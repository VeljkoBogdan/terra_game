#include "textureAtlasBuilder.h"

struct ImageEntry {
    std::string name;
    Image image;
};

struct Point {
    int x;
    int y;
};

TextureAtlas TextureAtlasBuilder::buildAtlas(const std::string& folder){
    TextureAtlas atlas; // init atlas
    std::cout << "Beginning Atlas Building..." << std::endl;
    // get full path to folder
    std::string path = folder;
    Image atlasImg = GenImageColor(8192, 8192, BLANK);
    Point pen = {0,0}; // init pen at 0, 0
    std::vector<ImageEntry> images;

    // check if the path exists and is a directory
    std::cout << "Checking folder path: " << path << std::endl;
    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) 
        throw std::runtime_error("Provided resource folder path not a directory");

    // iterate through the folder's contents
    std::cout << "Iterating through files in the folder..." << std::endl;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_regular_file(entry)) continue;
        auto filepath = entry.path();
        // extract extension (includes dot)
        std::string extension = filepath.extension().string();
        // check extension png
        if (extension == ".png") {
            Image fileImg = LoadImage(filepath.string().c_str());
            // check if the image is NOT valid
            if (!IsImageValid(fileImg)) continue;
            images.push_back({ filepath.stem().string(), fileImg });
        }
    }

    // sort images in descending order based on texture size
    std::sort(images.begin(), images.end(), [](const ImageEntry& first, const ImageEntry& second) {
        return (first.image.height * first.image.width) > (second.image.height * second.image.width); // comparator func
    });

    // add images to the atlas
    // keep the lowest texture's point of the first row as the next row's starting y position
    // make sure the width and height doesn't excede the atlas width and height
    int lowestY = 0;
    int lastLowestY = 0;
    for (auto& imageEntry : images) {
        auto& image = imageEntry.image;
        // if at any point adding the image exceeds the width or height, we break the loop
        if (pen.x + image.width > atlasImg.width) {
            pen.x = 0;
            pen.y = lowestY;
            lastLowestY = lowestY;
        }
        if (pen.y + image.height > atlasImg.height) {
            std::cout << "Textures exceeded atlas limit!" << std::endl;
            break;
        }
        
        Rectangle src = Rectangle{0, 0, image.width, image.height};
        Rectangle dst = Rectangle{pen.x, pen.y, image.width, image.height};
        ImageDraw(&atlasImg, image, src, dst, WHITE);
        atlas.addEntry(imageEntry.name, dst);

        lowestY = std::max(lowestY, image.height + lastLowestY);
        pen.x += image.width;
    }

    // cleanup
    for (auto& imageEntry : images) {
        UnloadImage(imageEntry.image);
    }

    // TEMP
    //ExportImage(atlasImg, "atlasTEMP.png");

    // return finished atlas
    atlas.setTexture(LoadTextureFromImage(atlasImg));
    UnloadImage(atlasImg);
    return atlas;
}