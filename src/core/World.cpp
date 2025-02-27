//
// Created by seirar on 2/27/2025.
//


module World;

void World::load_world() {
    if (!map_list.empty()) {
        current_world = map_list[0];
    }
}

void World::load_maps(SDL_Renderer* renderer) {
    auto huanlejiedong = new Map();
    huanlejiedong->load(renderer, "assets/map/huanlejiedong.png", "assets/map/huanlejiedong_mask.bmp");
    map_list.emplace(0, huanlejiedong);
}
