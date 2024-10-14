#include "EcsController.hpp"


std::unordered_map<pk::MapId, std::unique_ptr<pk::EcsController::ecs_instance_t>> pk::EcsController::ecsInstanceMap{};
pk::EcsController::ecs_instance_t* pk::EcsController::currentEcsInstance{nullptr};
