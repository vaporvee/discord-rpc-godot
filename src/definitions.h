#define BIND_METHOD(class_name, method, ...) godot::ClassDB::bind_method(D_METHOD(#method, ##__VA_ARGS__), &class_name::method)
#define BIND_SET_GET(class_name, property_name, variant_type, ...)                                                  \
    godot::ClassDB::bind_method(D_METHOD("get_" #property_name), &class_name::get_##property_name);                 \
    godot::ClassDB::bind_method(D_METHOD("set_" #property_name, #variant_type), &class_name::set_##property_name);  \
    godot::ClassDB::add_property(class_name::get_class_static(), PropertyInfo(variant_type, #property_name, ##__VA_ARGS__), "set_" #property_name, "get_" #property_name)
#define BIND_SIGNAL(signal_name, ...) ADD_SIGNAL(MethodInfo(#signal_name, ##__VA_ARGS__))
// getter isn't mandatory for this project
#define SET_GET(class_name, variable, setter, ...) decltype(class_name::variable) class_name::get_##variable() { return variable; } void class_name::set_##variable(decltype(class_name::variable) value) { variable = value; setter; }

#define RESOLVE_TYPE(default_value) \
    typename std::conditional<std::is_same<decltype(default_value), int>::value, int64_t, decltype(default_value)>::type

#define H_SET_GET(property_name, default_value) private: RESOLVE_TYPE(default_value) property_name = default_value; public: RESOLVE_TYPE(default_value) get_##property_name(); void set_##property_name(RESOLVE_TYPE(default_value) value);