#include <Vectoid/DataSet/KDTree.h>

#include <algorithm>
#include <cassert>
#include <limits>
#include <K/Core/Log.h>
#include <Vectoid/DataSet/Points.h>

using std::shared_ptr;
using std::to_string;
using std::unordered_set;
using std::vector;
using K::Core::Log;
using Vectoid::Core::Axis;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

KDTree::KDTree(const shared_ptr<Points> &points)
        : points_(points),
          depth_(0) {
    root_ = -1;
    if (points_->Size()) {
        vector<int> indices;
        for (int i = 0; i < points_->Size(); ++i) {
            indices.push_back(i);
        }
        root_ = AddSubTree(indices, 0, points_->Size(), 1);
        Log::Print(Log::Level::Debug, this, [&]{ return "kD-tree generated, depth=" + to_string(depth_); });
    } else {
        Log::Print(Log::Level::Warning, this, [&]{ return "empty kD-tree!"; });
    }
}

bool KDTree::QueryNearestNeighbor(const Vector<float> &queryPoint, int *outNearestNeighbor) {
    if (root_ != -1) {
        *outNearestNeighbor = FindNearestNeighbor(queryPoint, root_);
        return true;
    } else {
        return false;
    }
}

void KDTree::QuerySphereIntersection(const Vector<float> &sphereCenter, float sphereRadius,
                                     vector<ItemIntersection> *outIntersections) {
    outIntersections->clear();
    if (root_ != -1) {
        PerformSphereQuery(sphereCenter, sphereRadius, root_, outIntersections);
    }
}

bool KDTree::CheckIntegrity() {
    if (root_ == -1) {
        return true;
    }

    unordered_set<int> points;
    CollectPoints(root_, &points);
    if (static_cast<int>(points.size()) != points_->Size()) {
        Log::Print(Log::Level::Warning, this, [&]{ return "bad number of points"; });
        return false;
    }

    for (int i = 0; i < static_cast<int>(nodes_.size()); ++i) {
        if (!CheckNode(i)) {
            Log::Print(Log::Level::Warning, this, [&]{ return "node " + to_string(i) + " bad"; });
            return false;
        }
    }

    return true;
}

int KDTree::AddSubTree(vector<int> &indices, int offset, int size, int depth) {
    assert(size > 0);
    if (depth > depth_) {
        depth_ = depth;
    }

    int splittingAxisIndex = depth % 3;

    if (size == 1) {
        nodes_.push_back(Node(splittingAxisIndex, 0.0f, indices[offset], -1));
    } else {
        // size >= 2...
        std::sort(indices.begin() + offset, indices.begin() + offset + size,
                  [&](const int &lhs, const int &rhs) -> bool {
            return ((*points_)[lhs][splittingAxisIndex] < (*points_)[rhs][splittingAxisIndex]);
        });

        int   median         = size / 2;    // Will be >= 1.
        float splittingCoord = (*points_)[indices[offset + median]][splittingAxisIndex];
        int   leftChild      = AddSubTree(indices, offset, median, depth + 1);
        int   rightChild     = AddSubTree(indices, offset + median, size - median, depth + 1);
        nodes_.push_back(Node(splittingAxisIndex, splittingCoord, leftChild, rightChild));
    }

    return static_cast<int>(nodes_.size()) - 1;
}

int KDTree::FindNearestNeighbor(const Vector<float> &queryPoint, int node) {
    Node &nodeInfo = nodes_[node];
    if (nodeInfo.rightChild == -1) {
        return nodeInfo.leftChild;    // We're a leaf.
    } else {
        int candidate;
        if (queryPoint[nodeInfo.splittingAxisIndex] < nodeInfo.splittingCoordinate) {
            candidate = FindNearestNeighbor(queryPoint, nodeInfo.leftChild);
            float candidateDistance = ((*points_)[candidate] - queryPoint).Length();
            if (IsRightSubTreeInReach(nodeInfo, queryPoint, candidateDistance)) {
                RefineNearestNeighbor(queryPoint, nodeInfo.rightChild, &candidate, &candidateDistance);
            }
            // Note: It is okay to do either left or right here, even though points with exactly matching splitting
            //       coordinate can be in the left as well in the right subtrees, because we do a refinement search for
            //       the other side anyways.
        } else {
            candidate = FindNearestNeighbor(queryPoint, nodeInfo.rightChild);
            float candidateDistance = ((*points_)[candidate] - queryPoint).Length();
            if (IsLeftSubTreeInReach(nodeInfo, queryPoint, candidateDistance)) {
                RefineNearestNeighbor(queryPoint, nodeInfo.leftChild, &candidate, &candidateDistance);
            }
        }

        return candidate;
    }
}

void KDTree::RefineNearestNeighbor(const Vector<float> &queryPoint, int node, int *inOutCandidate,
                                   float *inOutCandidateDistance) {
    Node &nodeInfo = nodes_[node];
    if (nodeInfo.rightChild == -1) {    // Leaf.
        float distance = ((*points_)[nodeInfo.leftChild] - queryPoint).Length();
        if (distance < *inOutCandidateDistance) {
            *inOutCandidate         = nodeInfo.leftChild;
            *inOutCandidateDistance = distance;
        }
    } else {
        if (IsLeftSubTreeInReach(nodeInfo, queryPoint, *inOutCandidateDistance)) {
            RefineNearestNeighbor(queryPoint, nodeInfo.leftChild, inOutCandidate, inOutCandidateDistance);
        }
        if (IsRightSubTreeInReach(nodeInfo, queryPoint, *inOutCandidateDistance)) {
            RefineNearestNeighbor(queryPoint, nodeInfo.rightChild, inOutCandidate, inOutCandidateDistance);
        }
    }
}

void KDTree::PerformSphereQuery(const Vector<float> &sphereCenter, float sphereRadius, int node,
                                vector<ItemIntersection> *outIntersections) {
    Node &nodeInfo = nodes_[node];
    if (nodeInfo.rightChild == -1) {    // We're a leaf.
        if (((*points_)[nodeInfo.leftChild] - sphereCenter).Length() <= sphereRadius) {
            outIntersections->push_back(ItemIntersection(nodeInfo.leftChild, (*points_)[nodeInfo.leftChild]));
        }
    } else {
        if (IsLeftSubTreeInReach(nodeInfo, sphereCenter, sphereRadius)) {
            PerformSphereQuery(sphereCenter, sphereRadius, nodeInfo.leftChild, outIntersections);
        }
        if (IsRightSubTreeInReach(nodeInfo, sphereCenter, sphereRadius)) {
            PerformSphereQuery(sphereCenter, sphereRadius, nodeInfo.rightChild, outIntersections);
        }
    }
}

bool KDTree::IsLeftSubTreeInReach(const Node &nodeInfo, const Vector<float> &queryPoint, float distance) {
    return queryPoint[nodeInfo.splittingAxisIndex] - distance <= nodeInfo.splittingCoordinate;
}

bool KDTree::IsRightSubTreeInReach(const Node &nodeInfo, const Vector<float> &queryPoint, float distance) {
    return queryPoint[nodeInfo.splittingAxisIndex] + distance >= nodeInfo.splittingCoordinate;
}

void KDTree::CollectPoints(int node, unordered_set<int> *points) {
    Node &nodeInfo = nodes_[node];
    if (nodeInfo.rightChild == -1) {
        points->insert(nodeInfo.leftChild);
    } else {
        CollectPoints(nodeInfo.leftChild, points);
        CollectPoints(nodeInfo.rightChild, points);
    }
}

bool KDTree::CheckNode(int node) {
    Node &nodeInfo = nodes_[node];
    if (nodeInfo.rightChild == -1) {
        return true;
    } else {
        unordered_set<int> points;
        CollectPoints(nodeInfo.leftChild, &points);
        for (int pointIndex : points) {
            if ((*points_)[pointIndex][nodeInfo.splittingAxisIndex] > nodeInfo.splittingCoordinate) {
                Log::Print(Log::Level::Error, this, [&]{
                    return "bad left subtree leaf " + (*points_)[pointIndex].ToString() + " under inner node (axis="
                        + to_string(nodeInfo.splittingAxisIndex) + ", split_coord="
                        + to_string(nodeInfo.splittingCoordinate);
                });
                return false;
            }
        }

        points.clear();
        CollectPoints(nodeInfo.rightChild, &points);
        for (int pointIndex : points) {
            if ((*points_)[pointIndex][nodeInfo.splittingAxisIndex] < nodeInfo.splittingCoordinate) {
                Log::Print(Log::Level::Error, this, [&]{
                    return "bad right subtree leaf " + (*points_)[pointIndex].ToString() + " under inner node (axis="
                        + to_string(nodeInfo.splittingAxisIndex) + ", split_coord="
                        + to_string(nodeInfo.splittingCoordinate);
                });
                return false;
            }
        }

        return true;
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
