//
// Created by Tomer Torgeman on 2019-03-07.
//

#include <cmath>
#include "Attack.h"

#define PROJECTILE_VELOCITY 25
Texture Attack::attack_texture;


Attack::Attack(vec2 pos) {
    width = 1000;
    height = 1000;
    position = {pos.x, pos.y};
    rotation = 0;
    scale = {0.06f,0.06f};
    this->init();
};

bool Attack::init() {
    // Loading shaders


//TODO seems to be problem loading texturee
    if (!attack_texture.is_valid()) {
        if (!attack_texture.load_from_file(textures_path("cannonball.png"))) {
            fprintf(stderr, "Failed to load cannon texture!");
            return false;
        }
    }

    // The position corresponds to the center of the texture
    float wr = attack_texture.width * 0.5f;
    float hr = attack_texture.height * 0.5f;



//    if (moveRight) {
//        ANIMATION_FRAME_H = 0.50f;
//        ANIMATION_FRAME_W = 0.33f;
//    } else if (moveLeft) {
//    } else if (moveUp) {
//        ANIMATION_FRAME_H = 0.25f;
//        ANIMATION_FRAME_W = 0.33f;
//        Frame = 0.5f;
//    } else if (moveDown) {
//    } else {
//        ANIMATION_FRAME_H = 0.25f;
//        ANIMATION_FRAME_W = 0.33f;
//    }

    TexturedVertex vertices[4];
    vertices[0].position = {-wr, +hr, -0.02f};
    vertices[0].texcoord = {0.f, 1.f};
    vertices[1].position = {+wr, +hr, -0.02f};
    vertices[1].texcoord = {1.f, 1.f};
    vertices[2].position = {+wr, -hr, -0.02f};
    vertices[2].texcoord = {1.f, 0.f};
    vertices[3].position = {-wr, -hr, -0.02f};
    vertices[3].texcoord = {0.f, 0.f};

    // counterclockwise as it's the default opengl front winding direction
    uint16_t indices[] = {0, 3, 1, 1, 3, 2};



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
    return effect.load_from_file(shader_path("attack.vs.glsl"), shader_path("attack.fs.glsl"));
}

void Attack::move() {

};

void Attack::travel(vec2 destination) {
    //printf("desx:%f, desty:%f\n", destination.x, destination.y);
    vec2 dir = {-position.x + destination.x ,  - position.y +  destination.y};
    float length = sqrt((dir.x * dir.x) + (dir.y * dir.y));
     // float angle = atan2(dir.y, dir.x) * 180 / 3.14f;

       // vec2 newPos = { (cos(angle * 3.14f/180) * PROJECTILE_VELOCITY), (sin(angle * 3.14f/180) * PROJECTILE_VELOCITY)};
//
//    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
//
//
        vec2 newPos = {(dir.x / length) * PROJECTILE_VELOCITY, (dir.y / length) * PROJECTILE_VELOCITY};
//
//        vec2 newPos = {position.x + dir.x * PROJECTILE_VELOCITY, position.y + dir.y * PROJECTILE_VELOCITY};

        position.x += newPos.x;
        position.y += newPos.y;

}


bool Attack::attackCondition(bool isFighting){
//    (world->lock->health > 0 || !GameObject->tooFar(world->selectedObject, world->lock)){

        if(isFighting) {
            travel(target);
            if (abs(position.x - target.x) < 15 && abs(position.y - target.y) < 15) {
                // attack->destroy();
                //free(attack);
                return true;
            }
        }
    return false;
}

void Attack::draw(const mat3 &projection) {
    transform_begin();
    transform_translate(position);
    transform_rotate(rotation);
    transform_scale(scale);
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
    GLint shift_uloc = glGetUniformLocation(effect.program, "shift");

    // Setting vertices and indices
    glBindVertexArray(mesh.vao);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

    // Input data location as in the vertex buffer
    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
    glEnableVertexAttribArray(in_position_loc);
    glEnableVertexAttribArray(in_texcoord_loc);
    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)0);
    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)sizeof(vec3));

    // Enabling and binding texture to slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, attack_texture.id);

    // Setting uniform values to the currently bound program
    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *)&transform);


//    glUniform3fv(color_uloc, 1, drawTint.data());
    glUniform2f(shift_uloc, texPiece.x , texPiece.y );
    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *)&projection);

    // Drawing!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
};

void Attack::destroy() {
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ibo);
    glDeleteBuffers(1, &mesh.vao);

    glDeleteShader(effect.vertex);
    glDeleteShader(effect.fragment);
    glDeleteShader(effect.program);
};