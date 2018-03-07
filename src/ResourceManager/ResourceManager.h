#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

template <typename Resource>
class ResourceManager
{
    using CrString = const std::string &;

  public:
    ResourceManager(CrString folder, CrString extention)
        : _folder("./res/" + folder + "/"), _extention("." + extention)
    {
    }

    const Resource &get(CrString name)
    {
        if (!exists(name)) //isn't in the list -> add to the list
        {
            add(name);
        }

        return _resources.at(name);
    }

    bool exists(CrString name) const
    {
        return _resources.find(name) != _resources.end();
    }

    void add(CrString name)
    {
        Resource r;

        //if the resource fails to load, then it adds a default "fail" resource
        if (!r.loadFromFile(getFullname(name)))
        {
            Resource fail;
            fail.loadFromFile(_folder + "_err_" + _extention);
            _resources.insert(std::make_pair(name, fail));
        }
        else
        {
            _resources.insert(std::make_pair(name, r));
        }
    }

  private:
    std::string getFullname(CrString name)
    {
        return _folder + name + _extention;
    }

    const std::string _folder;
    const std::string _extention;

    std::unordered_map<std::string, Resource> _resources;
};