#include "Raytracer.hpp"

#include <cmath>
#include <iostream>


namespace rt
{

Raytracer::Image Raytracer::getImage()
{
    return buffer_;
}

void Raytracer::load(scene::Scene& s)
{
    scene_ = s;
}

void Raytracer::run()
{
    for(int height=-IMG_SIDE/2; height < IMG_SIDE/2; height++)
    {
        for(int width =- IMG_SIDE/2; width<IMG_SIDE/2; width++)
        {
            core::Point orgin(width, height, 0.0);
            core::Vector direction(0.0,0.0,-1.0);

            core::Ray viewRay(orgin, direction);

            core::Color c = trace(viewRay, 1);
            buffer_[width+IMG_SIDE/2][height+IMG_SIDE/2] = c;
        }
    }
    logger_.dbg() << "Hit: " << hitCounter_;
    logger_.dbg() << "NoHit: " << noHitCounter_;
    logger_.inf() << "Hit ratio: " << (static_cast<float>(hitCounter_)/(hitCounter_+ noHitCounter_) * 100.0) << "\%";
}

core::Color Raytracer::trace(core::Ray& ray, int recursiveStep)
{
    core::Color local = {0.0,0.0,0.0};

    double distance = 1000000.0f;

    auto objects = scene_.getObjects();

    core::Object::Ptr closestObject = nullptr;

    for(auto& object : objects)
    {

        double temporaryDistance = distance;

        if(object->hit(ray, temporaryDistance))
        {
            hitCounter_++;
            if(temporaryDistance < distance)
            {
                distance = temporaryDistance;
                closestObject = object;
            }

        }
        else
        {
            noHitCounter_++;    
        }
    };

    if (closestObject == nullptr)
    {
        return core::Color{0.0,0.0,0.0};
    }

    core::Point collision = ray.getOrgin() + ray.getDirection() * distance;
    core::Vector normal = closestObject->getNormalAt(collision);

    auto lights = scene_.getLights();
    for(auto& light : lights)
    {
        // core::Vector distance = light->getPosition() - collision;

        // double t = sqrtf(distance.dotProduct(distance));

        // PHONG lighting model
        double a = 1.0;
        double b = 0.01;
        double c = 0.001;

        core::Vector V = ray.getDirection();    // observation vector
        core::Vector L = light->getPosition() - collision; // light incidence vector
        V.normalize();
        L.normalize();

        double dotNL = normal.dotProduct(L);

        core::Vector R = L - (normal * (2.0 * dotNL));    //reflected vector
        R.normalize();

        double dotVR = R.dotProduct(V) * 1.1; // angle betwen observation vector and reflected vector

        if (dotVR < 0) dotVR = 0;

        core::Vector difference = light->getPosition() - collision;
        double di = sqrtf(difference.getX() * difference.getX() +
            difference.getY() * difference.getY() + 
            difference.getZ() * difference.getZ());

        //local += closestObject->

                    //object Color                       //light color                     //some weird phong sh*t

        local = local + core::Color{127.0,127.0,255.0} + core::Color{255.0,255.0,255.0} * (0.5/ (a+ b*di + c*di*di));

    }

    if (local.red >= 255) local.red = 254;
    if (local.green >= 255) local.green = 254;
    if (local.blue >= 255) local.blue = 254;

    return local;
}



}  // namespace rt