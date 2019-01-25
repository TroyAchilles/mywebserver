#ifndef FACTORY_H
#define FACTORY_H
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <type_traits>
template <class Obj, typename... ObjArgs>
class factory
{
    public:
        static factory&  instance()
        {
            static factory _sfactory;
            return _sfactory;
        }

        std::vector<std::string> listsuport(bool bprint = false)
        {
            std::vector<std::string>  vec;
            for (auto& item : _map)
            {
                if (bprint)
                    std::cout << item.first << std::endl;
                vec.push_back(item.first);
            }
            return vec;
        }

        std::shared_ptr<Obj> produce(std::string key, ObjArgs... args)
        {
            if (_map.find(key) == _map.end())
                return std::shared_ptr<Obj>(0);
            return std::shared_ptr<Obj>(_map[key](args...));
        }

#ifdef TUPLE_V
        std::shared_ptr<Obj> produce(std::string key, std::tuple<ObjArgs...> args)
        {
            return std::shared_ptr<Obj>(0);
        }
#endif

    private:
        factory() = default;
        factory(const factory& ) = delete;
        factory(factory&& ) = delete;
    public:
        std::map<std::string, std::function<Obj*(ObjArgs...)>> _map;

    public:
#if 0
        //偏特化，非衍生类可以编译过，但是在运行时抛出异常
        template <typename T , typename T1 = void>
        struct register_t
        {
            register_t(const std::string& key)
            {
                (void)key;
                auto info =  std::string(typeid(T).name()) + std::string(" is not derive from ") + std::string(typeid(Obj).name());
                std::cout << info << std::endl;
                throw info;
            }
        };

        template <typename T>
        struct register_t<T, typename std::enable_if<std::is_base_of<Obj,T>::value>::type>
        {
            register_t(const std::string& key)
            {
                factory::instance()._map.emplace(key, [](ObjArgs... args){
                    return new T(args...);
                });
            }
        };
#else
        template <typename T>
        struct register_t
        {
            register_t(const std::string& key)
            {
                factory::instance()._map.emplace(key, [](ObjArgs... args){
                    return new T(args...);
                });
            }

            //用来定位错误的注册，非衍生类会直接编译报错
            typename std::enable_if<std::is_base_of<Obj,T>::value, char>::type pass;
        };
#endif
};

#endif // FACTORY_H
