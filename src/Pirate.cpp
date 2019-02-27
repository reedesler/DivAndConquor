//
// Created by Tomer Torgeman on 2019-02-20.
//

#include <cmath>
#include "Pirate.h"
#include "Common.hpp"
#include "World/GameObject.hpp"

Texture Pirate::pirate_texture;
int ANIMATION_SPEED;
const int NUM_FRAMES = 3;
float ANIMATION_FRAME_H = 0.75f;
float ANIMATION_FRAME_W = 0.33f;
float Frame = 0.5f;

Pirate::Pirate(World *world, vec2 pos): GameObject(world), Renderable(){
    w = 75;
    h = 50;
    //if (!sprite.init(w, h, textures_path("captain.png"), {0.33f, 0.25f}))
    //{
    //    printf("ERROR initializing sprite\n");
    //}
    position = pos;
    rotation = 0;
    scale = {1.f, 1.f};
    selected = false;
    init();
}

bool Pirate::init() {
    // Load shared texture
    if (!pirate_texture.is_valid()) {
        if (!pirate_texture.load_from_file(textures_path("captain.png"))) {
            fprintf(stderr, "Failed to load turtle texture!");
            return false;
        }
    }

    // The position corresponds to the center of the texture
    float wr = pirate_texture.width * 0.5f;
    float hr = pirate_texture.height * 0.5f;



    if (moveRight) {
         ANIMATION_FRAME_H = 0.50f;
         ANIMATION_FRAME_W = 0.33f;
    } else if (moveLeft) {
    } else if (moveUp) {
         ANIMATION_FRAME_H = 0.25f;
         ANIMATION_FRAME_W = 0.33f;
         Frame = 0.5f;
    } else if (moveDown) {
    } else {
         ANIMATION_FRAME_H = 0.25f;
         ANIMATION_FRAME_W = 0.33f;
    }

    TexturedVertex vertices[4];
    vertices[0].position = {-wr, +hr, -0.02f};
    vertices[0].texcoord = {0.f, ANIMATION_FRAME_H};
    vertices[1].position = {+wr, +hr, -0.02f};
    vertices[1].texcoord = {ANIMATION_FRAME_W, ANIMATION_FRAME_H};
    vertices[2].position = {+wr, -hr, -0.02f};
    vertices[2].texcoord = {ANIMATION_FRAME_W, 0.f};
    vertices[3].position = {-wr, -hr, -0.02f};
    vertices[3].texcoord = {0.f, 0.f};

    // counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = {0, 3, 1, 1, 3, 2};

    // Clearing errors
    gl_flush_errors();

    // Vertex Buffer creation
//    glGenBuffers(1, &mesh.vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);
//
//    // Index Buffer creation
//    glGenBuffers(1, &mesh.ibo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);
//
//    // Vertex Array (Container for Vertex + Index buffer)
//    glGenVertexArrays(1, &mesh.vao);
//    if (gl_has_errors())
//        return false;
//
//    // Loading shaders
//    if (!effect.load_from_file(shader_path("pirate.vs.glsl"), shader_path("pirate.fs.glsl")))
//        return false;

    // Setting initial values, scale is negative to make it face the opposite way
    // 1.0 would be as big as the original texture
    //p_position = {200, 200};
    rotation = 0;
    scale = {0.5f, 0.5f};

    moveDown = false;
    moveLeft = false;
    moveRight = false;
    moveUp = false;

    gl_flush_errors();

    // Vertex Buffer creation
    glGenBuffers(1, &mesh.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);

    // Index Buffer creation
    glGenBuffers(1, &mesh.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

    // Vertex Array (Container for Vertex + Index buffer)
    glGenVertexArrays(1, &mesh.vao);
    if (gl_has_errors())
        return false;

    // Loading shaders
    return effect.load_from_file(shader_path("pirate.vs.glsl"), shader_path("pirate.fs.glsl"));
}

// Call if init() was successful
// Releases all graphics resources
//void Pirate::destroy() {
//    glDeleteBuffers(1, &mesh.vbo);
//    glDeleteBuffers(1, &mesh.ibo);
//    glDeleteBuffers(1, &mesh.vao);
//
//    glDeleteShader(effect.vertex);
//    glDeleteShader(effect.fragment);
//    glDeleteShader(effect.program);
//}

void Pirate::update(float ms) {
    // Move fish along -X based on how much time has passed, this is to (partially) avoid
    // having entities move at different speed based on the machine.
    const float PIRATE_SPEED = 20.f;
    float step = -PIRATE_SPEED * (ms / 1000);
   // p_position.x += step;
    float distance = PIRATE_SPEED * (ms / 100);

    if (moveRight) {

        move({distance, 0.f});
    } else if (moveLeft) {
        move({-distance, 0.f});
    } else if (moveUp) {
        move({0.f, -distance});
    } else if (moveDown) {
        move({0.f, distance});
    }

}

void Pirate::move(vec2 off) {
    if (onTerrain(off, 2)){
        position.x = off.x;
        position.y = off.y;
    }

}

void Pirate::moveToPos(vec2 pos) {
//    for(int i = p_position.x; i < pos.x; i++){
//        p_position.x = p_position.x + 1;
//        for (int j = p_position.y; j < pos.y; ++j) {
//            p_position.y = p_position.y + 1;
//            break;
//        }
//    }
    position = pos;

}

void Pirate::movement(vec2 pos) {
//    for(int i = p_position.x; i < pos.x; i++){
//        p_position.x = p_position.x + 1;
//        for (int j = p_position.y; j < pos.y; ++j) {
//            p_position.y = p_position.y + 1;
//            break;
//        }
//    }
    position.x = position.x + pos.x;
    position.y = position.y + pos.y;

}

void Pirate::updateFrame(float ms) {
    // Move fish along -X based on how much time has passed, this is to (partially) avoid
    // having entities move at different speed based on the machine.
//    elapsedTime += ms;
//    if(elapsedTime > ANIMATION_SPEED){
//        frame = (frame +1)%NUM_FRAMES;
//    }
}
void Pirate::setSelected(){
    this->selected = !this->selected;
}
void Pirate::draw(const mat3 &projection) {
    // Transformation code, see Rendering and Transformation in the template specification for more info
    // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
    transform_begin();
    transform_translate({position.x, position.y});
    transform_scale(scale);
    transform_rotate(rotation);
    transform_end();


    // Setting shaders
    glUseProgram(effect.program);

    // Enabling alpha channel for textures
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    // Getting uniform locations for glUniform* calls
    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
    GLint texcoordShiftLoc = glGetUniformLocation(effect.program, "shift");

    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");

    //GLint moveLeft = glGetAttribLocation(effect.program, "moveLeft");

   // glEnableVertexAttribArray(moveLeft);
  // glEnableVertexAttribArray(texcoordShiftLoc);
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    //glVertexAttribPointer(moveLeft, 3, GL_BOOL, GL_FALSE, sizeof(TexturedVertex), (void *) 0);

    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) 0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pirate_texture.id);

    // Setting uniform values to the currently bound program

        if (moveRight) {

                ANIMATION_FRAME_H = 0.25f;
                ANIMATION_FRAME_W = 0.33f;



        } else if (moveLeft) {
            ANIMATION_FRAME_H = 0.75f;
            ANIMATION_FRAME_W = 0.33f;
        } else if (moveUp) {
            ANIMATION_FRAME_H = 0.0f;
            ANIMATION_FRAME_W = 0.33f;
            Frame = 0.5f;
        } else if (moveDown) {
            ANIMATION_FRAME_H = 0.5f;
            ANIMATION_FRAME_W = 0.33f;
            Frame = 0.75;
        } else {
            ANIMATION_FRAME_H = 0.25f;
            ANIMATION_FRAME_W = 0.33f;
        }

    if (selected)
        tint = {0.7f, 1.f, 0.7f};
    else
        tint = {1.f, 1.f, 1.f};
    glUniform3fv(color_uloc, 1, tint.data());

    glUniform2f(texcoordShiftLoc, ANIMATION_FRAME_W, ANIMATION_FRAME_H);
    //glUniform2f(texcoordShiftLoc, 0.25f, 0.f);


    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *) &transform);
    float color[] = {1.f, 1.f, 1.f};
    //glUniform3fv(color_uloc, 1, tint.data());
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

//    transform_begin();
//
//    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    // SALMON TRANSFORMATION CODE HERE
//
//    // see Transformations and Rendering in the specification pdf
//    // the following functions are available:
//    // transform_translate()
//    // transform_rotate()
//    // transform_scale()
//
//    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//    // REMOVE THE FOLLOWING LINES BEFORE ADDING ANY TRANSFORMATION CODE
//    transform_translate({p_position.x, p_position.y});
//    transform_scale(p_scale);
//    transform_rotate(p_rotation);
//    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//
//    transform_end();
//
//    // Setting shaders
//    glUseProgram(effect.program);
//
//    // Enabling alpha channel for textures
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_DEPTH_TEST);
//
//    // Getting uniform locations
//    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
//    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
//    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
//    GLint light_up_uloc = glGetUniformLocation(effect.program, "light_up");
//
//    // Setting vertices and indices
//    glBindVertexArray(mesh.vao);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
//
//    // Input data location as in the vertex buffer
//    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
//    GLint in_color_loc = glGetAttribLocation(effect.program, "in_color");
//    glEnableVertexAttribArray(in_position_loc);
//    glEnableVertexAttribArray(in_color_loc);
//    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
//    glVertexAttribPointer(in_color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(vec3));
//
//    // Setting uniform values to the currently bound program
//    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *) &transform);
//
//    // !!! Salmon Color
//    float color[] = {1.f, 1.f, 1.f};
//
//
//    glUniform3fv(color_uloc, 1, color);
//    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);
//
//
//
//    // Drawing!
//    glDrawElements(GL_TRIANGLES, (GLsizei) m_num_indices, GL_UNSIGNED_SHORT, nullptr);
}

vec2 Pirate::get_position() const {
    return position;
}

void Pirate::set_position(vec2 position) {
    this->position = position;
}

// Returns the local bounding coordinates scaled by the current size of the turtle
vec2 Pirate::get_bounding_box() const {
    // fabs is to avoid negative scale due to the facing direction
    return {std::fabs(scale.x) * pirate_texture.width, std::fabs(scale.y) * pirate_texture.height};
}

//bounds Pirate::getBounds() {
//    return {p_position.x - pirate_texture.width / 2, p_position.x + pirate_texture.width / 2,
//            p_position.y - pirate_texture.height / 2, p_position.y + pirate_texture.height / 2};
//}
