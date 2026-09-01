#pragma once
#include "Texture.h"


class TextureManager
{
public:
    static TextureManager* Get();

    void Clear();
    void SetTexture(const std::string& fileName);
    void SetAddressMode(AddressMode addressMode);
    void SetUseFilter(bool useFilter);

    // "Hack" is to use color with -z to flag color as uv coordinates
    X::Color SampleColor(const X::Color& uv) const;

private:
    std::vector<std::unique_ptr<Texture>> mTextures;
    const Texture* mCurrentTexture = nullptr;
    bool mUseFilter = false;
    AddressMode mAddressMode = AddressMode::Clamp;

};