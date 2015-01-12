#include "TextConsole.h"

#include <Vectoid/OpenGL.h>

#include "Glyphs.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

TextConsole::TextConsole(int width, int height, shared_ptr<Glyphs> glyphs)
        : width_(width),
          height_(height),
          glyphs_(glyphs) {
}

void TextConsole::Render(RenderContext *context) {
    GLfloat vertices[]  = { 0.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f, 
                            1.0f, 1.0f, 0.0f,
                           
                            0.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,
                            0.0f, 1.0f, 0.0f  };
    
    GLfloat texCoords[] = { 0.0f, 0.0f,
                            1.0f, 0.0f, 
                            1.0f, 1.0f,
                            
                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f  };
    
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glyphs_->BindGlyphTexture(65);    // A.
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

}    // Namespace Raspiator.

