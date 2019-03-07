//
// Created by Tomer Torgeman on 2019-03-05.
//

#include "World/GameObject.hpp"
#include "Common.hpp"
//Texture Sailor::sailor_texture;

float ANIMATION_FRAME_HS = 0.75f;
float ANIMATION_FRAME_WS = 0.33f;
#define SAILOR_VELOCITY 5


Sailor::Sailor(World *world, vec2 pos): GameObject(world, pos){
    w = 75;
    h = 75;

    if (!sprite.init(w, h, textures_path("sailor.png"), {0.33f, 0.25f}))
    {
        printf("ERROR initializing sprite\n");
    }
    rotation = 0;
    scale = {1.f, 1.f};
    landUnit = true;
    pathfinder = new Pathfinder(world);
   // init();
}

void Sailor::move(vec2 pos) {

    TilePos start = Tilemap::getTilePos(position.x, position.y);
    TilePos goal = Tilemap::getTilePos(pos.x, pos.y);
    pathfinder->init(start.x, start.y, goal.x, goal.y);
    pathfinder->replan();
    path = pathfinder->getPath();
    //if (onTerrain(pos, 2) || onTerrain(pos, 1)){
    //    position.x = pos.x;
    //    position.y = pos.y;
    //
    //}
}

void Sailor::update() {
    world->setExplored(position, 7 * TILE_SIZE);
    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next == path.path.end()) return;
        float destX = next->x * TILE_SIZE;
        float destY = next->y * TILE_SIZE;
        if (abs(position.x - destX) <= SAILOR_VELOCITY && abs(position.y - destY) <= SAILOR_VELOCITY) {
            pathfinder->updateStart(next->x, next->y);
            pathfinder->replan();
            path = pathfinder->getPath();
        } else {
            travel({destX, destY});
        }
    }
}

void Sailor::travel(vec2 destination) {
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > SAILOR_VELOCITY) {

        renderDirection(dir);

        dir = {dir.x / length, dir.y / length};

        vec2 newPos = {position.x + dir.x * SAILOR_VELOCITY, position.y + dir.y * SAILOR_VELOCITY};
        position = newPos;
    }
}

void Sailor::renderDirection(vec2 dir){
    if(frameNo > 1){
        frameNo = 0;
    }
    if(dir.x > 0 && abs(dir.x)  > abs(dir.y)){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.25f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else if (dir.x < 0){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.75f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else if (dir.y > 0 && abs(dir.x) < abs(dir.y)){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.5f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else {
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    }

    if (r % 3 == 0){
        frameNo = frameNo + 0.333f;
    }
}

//bool Sailor::init() {
//    // Load shared texture
//    if (!sailor_texture.is_valid()) {
//        if (!sailor_texture.load_from_file(textures_path("sailor.png"))) {
//            fprintf(stderr, "Failed to load turtle texture!");
//            return false;
//        }
//    }
//
//    // The position corresponds to the center of the texture
//    float wr = sailor_texture.width * 0.5f;
//    float hr = sailor_texture.height * 0.5f;
//
//
//
////    if (moveRight) {
////        ANIMATION_FRAME_H = 0.50f;
////        ANIMATION_FRAME_W = 0.33f;
////    } else if (moveLeft) {
////    } else if (moveUp) {
////        ANIMATION_FRAME_H = 0.25f;
////        ANIMATION_FRAME_W = 0.33f;
////    } else if (moveDown) {
////    } else {
////        ANIMATION_FRAME_H = 0.25f;
////        ANIMATION_FRAME_W = 0.33f;
////    }
//
//    TexturedVertex vertices[4];
//    vertices[0].position = {-wr, +hr, -0.02f};
//    vertices[0].texcoord = {0.f, ANIMATION_FRAME_HS};
//    vertices[1].position = {+wr, +hr, -0.02f};
//    vertices[1].texcoord = {ANIMATION_FRAME_WS, ANIMATION_FRAME_HS};
//    vertices[2].position = {+wr, -hr, -0.02f};
//    vertices[2].texcoord = {ANIMATION_FRAME_WS, 0.f};
//    vertices[3].position = {-wr, -hr, -0.02f};
//    vertices[3].texcoord = {0.f, 0.f};
//
//    // counterclockwise as it's the default opengl front winding direction
//    uint16_t indices[] = {0, 3, 1, 1, 3, 2};
//
//    // Clearing errors
//    gl_flush_errors();
//
//    // Setting initial values, scale is negative to make it face the opposite way
//    // 1.0 would be as big as the original texture
//    //p_position = {200, 200};
//    rotation = 0;
//    scale = {0.5f, 0.5f};
//
////    moveDown = false;
////    moveLeft = false;
////    moveRight = false;
////    moveUp = false;
//
//    gl_flush_errors();
//
//    // Vertex Buffer creation
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
//    return effect.load_from_file(shader_path("sailor.vs.glsl"), shader_path("sailor.fs.glsl"));
//}

//void Sailor::setSelected(){
//    this->selected = !this->selected;
//}
//void Sailor::draw(const mat3 &projection) {
//    // Transformation code, see Rendering and Transformation in the template specification for more info
//    // Incrementally updates transformation matrix, thus ORDER IS IMPORTANT
//    transform_begin();
//    transform_translate({position.x, position.y});
//    transform_scale(scale);
//    transform_rotate(rotation);
//    transform_end();
//
//
//    // Setting shaders
//    glUseProgram(effect.program);
//
//    // Enabling alpha channel for textures
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glDisable(GL_DEPTH_TEST);
//
//    // Getting uniform locations for glUniform* calls
//    GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
//    GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
//    GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
//    GLint texcoordShiftLoc = glGetUniformLocation(effect.program, "shift");
//
//    // Setting vertices and indices
//    glBindVertexArray(mesh.vao);
//    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
//
//    // Input data location as in the vertex buffer
//    GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
//    GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
//
//    //GLint moveLeft = glGetAttribLocation(effect.program, "moveLeft");
//
//    // glEnableVertexAttribArray(moveLeft);
//    // glEnableVertexAttribArray(texcoordShiftLoc);
//    glEnableVertexAttribArray(in_position_loc);
//    glEnableVertexAttribArray(in_texcoord_loc);
//    //glVertexAttribPointer(moveLeft, 3, GL_BOOL, GL_FALSE, sizeof(TexturedVertex), (void *) 0);
//
//    glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) 0);
//    glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *) sizeof(vec3));
//
//    // Enabling and binding texture to slot 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, sailor_texture.id);
//
//    // Setting uniform values to the currently bound program
//
////    if (moveRight) {
////
////        ANIMATION_FRAME_HS = 0.25f;
////        ANIMATION_FRAME_WS = 0.33f;
////
////
////
////    } else if (moveLeft) {
////        ANIMATION_FRAME_HS = 0.75f;
////        ANIMATION_FRAME_WS = 0.33f;
////    } else if (moveUp) {
////        ANIMATION_FRAME_HS = 0.0f;
////        ANIMATION_FRAME_WS = 0.33f;
////    } else if (moveDown) {
////        ANIMATION_FRAME_HS = 0.5f;
////        ANIMATION_FRAME_WS = 0.33f;
////    } else {
////        ANIMATION_FRAME_HS = 0.25f;
////        ANIMATION_FRAME_WS = 0.33f;
////    }
//
//    if (selected)
//        tint = {0.7f, 1.f, 0.7f};
//    else
//        tint = {1.f, 1.f, 1.f};
//    glUniform3fv(color_uloc, 1, tint.data());
//
//    glUniform2f(texcoordShiftLoc, ANIMATION_FRAME_WS, ANIMATION_FRAME_HS);
//    //glUniform2f(texcoordShiftLoc, 0.25f, 0.f);
//
//
//    glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *) &transform);
//    float color[] = {1.f, 1.f, 1.f};
//    //glUniform3fv(color_uloc, 1, tint.data());
//    glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *) &projection);
//
//    // Drawing!
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
//
//}