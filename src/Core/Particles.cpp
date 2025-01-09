///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/Particles.h>

#include <K/Core/NumberTools.h>

using namespace std;
using namespace K::Core;

namespace Vectoid {
namespace Core {

Particles::Particles()
        : particles_(1),
          random1000_(uniform_int_distribution<>(0, 1000)) {
}

Particles::ParticleInfo &Particles::Add(const Vector<float> &position, const Vector<float> &velocity,
                                        int *outStorageId) {
    int storageId;
    ParticleInfo &particle = particles_.Get(0, &storageId);
    particle.position = position;
    particle.velocity = velocity;
    particle.age      = 0.0f;
    particle.hidden   = false;
    if (!particle.random0) {
        // Use random generator only once for each particle info: initially.
        particle.random0 = (float)random1000_(randomEngine_)/500.0f - 1.0f;
        particle.random1 = (float)random1000_(randomEngine_)/500.0f - 1.0f;
        NumberTools::Clamp(particle.random0, -1.0f, 1.0f);
        NumberTools::Clamp(particle.random1, -1.0f, 1.0f);

    }
    if (outStorageId) {
        *outStorageId = storageId;
    }
    return particle;
}

void Particles::Remove(int id) {
    particles_.Put(id);
}

Particles::ParticleInfo &Particles::Get(int id) {
    return particles_.Item(id);
}

int Particles::Count() {
    return particles_.Count() - particles_.IdleCount();
}

Particles::ParticleInfo::ParticleInfo()
    : age(0.0f),
      hidden(false),
      random0(0.0f),
      random1(0.0f) {
}

}    // Namespace Core.
}    // Namespace Vectoid.
