#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <stdio.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Discord_Activity : public Object
{
    GDCLASS(Discord_Activity, Object);

    static Discord_Activity *singleton;

protected:
    static void _bind_methods();

private:
    int64_t app_id;
    String state;
    String details;

    String large_image;
    String large_image_text;
    String small_image;
    String small_image_text;

public:
    static Discord_Activity *get_singleton();

    Discord_Activity();
    ~Discord_Activity();

    void debug();
    void coreupdate();
    void refresh();

    int64_t get_app_id() const;
    void set_app_id(const int64_t &value);
    String get_state() const;
    void set_state(const String &value);
    String get_details() const;
    void set_details(const String &value);

    String get_large_image() const;
    void set_large_image(const String &value);
    String get_large_image_text() const;
    void set_large_image_text(const String &value);
    String get_small_image() const;
    void set_small_image(const String &value);
    String get_small_image_text() const;
    void set_small_image_text(const String &value);
};

#endif