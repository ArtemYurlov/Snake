#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "includes.h"

template <typename Resource>
class ResourceManager
{
    using CrString = const std::string &;

  public:
    ResourceManager(CrString folder, CrString extention)
        : _folder("./res/" + folder + "/"), _extention("." + extention)
    {
        initializeDataSizePairs(dataSizePairs); // from includes.h which gives us dataSizePairs
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
        // if (!r.loadFromFile(getFullname(name)))
        // {
        //     Resource fail;
        //     fail.loadFromFile(_folder + "_err_" + _extention);
        //     _resources.insert(std::make_pair(name, fail));
        // }
        // else
        // {
        //     _resources.insert(std::make_pair(name, r));
        // }
        
        //loadding from memory
        std::pair<const void*, const std::size_t> resInMem = dataSizePairs.at(getVarName(name));
        if(r.loadFromMemory(resInMem.first, resInMem.second))
        {
            _resources.insert(std::make_pair(name, r));
        }
        else
        {
            std::pair<const void*, const std::size_t> failInMem = dataSizePairs.at(getVarName("_err_")); //NOTE MIGHT FAIL ITSELF
            Resource fail;
            fail.loadFromMemory(failInMem.first, failInMem.second);
            _resources.insert(std::make_pair(name, fail));
            //std::cout << "RES " << name << " failed to load from memory!";
        }
    }

  private:
    std::string getVarName (CrString name)
    {
        return std::string(name) + "_" + std::string(_extention).substr(1,_extention.size());
    }
    
    std::string getFullname(CrString name)
    {
        return _folder + name + _extention;
    }

    const std::string _folder;
    const std::string _extention;

    std::unordered_map<std::string, Resource> _resources;
    std::unordered_map<std::string, std::pair<const void*, const std::size_t>> dataSizePairs;
};