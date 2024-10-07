import pygame
from pytmx.util_pygame import load_pygame
from pytmx.pytmx import TiledMap, TiledTileLayer, TiledObjectGroup, TiledObject
from enum import Enum, auto


class MapId(Enum):

    World = auto()


MAPS = {
    MapId.World: ("../src/assets/data/maps/world.tmx", "../src/assets/data/maps/world.txt")
}


def main() -> None:
    display = pygame.display.set_mode((200, 200))
    pygame.display.set_caption("TiledMap")
    map_id = MapId.World

    tiled_map: TiledMap = load_pygame(MAPS[map_id][0])
    output_file = MAPS[map_id][1]
    
    with open(output_file, "w+") as file:
        for i in tiled_map:
            if (isinstance(i, TiledObjectGroup)):
                i: TiledObjectGroup
                file.write(f"{i.name}\n")
                file.write(f"{len(i)}\n")                
                try:
                    for tile in i:
                        tile: TiledObject
                        match i.name:
                            case "Arena":
                                file.write(f"{tile.properties['attribute']} {tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Trees":
                                file.write(f"{tile.properties['tree-type']} {tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Monsters":
                                file.write(f"{tile.properties['poke-type']} {tile.x:.2f} {tile.y:.2f}\n")
                            case "Transition":
                                file.write(f"{tile.properties['transition-type']} {tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f}\n")
                            case "Pillar":
                                file.write(f"{tile.properties['pillar']} {tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Palm":
                                file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Rock":
                                file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Sprites":
                                file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Hospital":
                                file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.properties['source'].replace('../tilesets/../../', './assets/')}\n")
                            case "Collision":
                                file.write(f"{tile.x:.2f} {tile.y:.2f} {tile.width:.2f} {tile.height:.2f}\n")
                            case _:
                                pass                        
                except Exception as e:
                    print(i.name, tile.properties, tile.x, tile.y, e)

                


if __name__ == "__main__":
    main()
