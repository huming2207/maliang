#pragma once

#include <array>
#include <utility>
#include <functional>
#include "pugixml.hpp"
#include "base_node.hpp"
#include "lvgl.h"

namespace lv::node
{
    class object : public base_node
    {
    public:
        const char *name() override
        {
            return "object";
        }

        def::state_t parse(const pugi::xml_node &node, lv_obj_t *obj) override
        {
            const def::markup_strategy<pugi::xml_attribute> attr_lut[] = {
                    LVML_ADD_ATTR_FUNC(parse_width, obj, "width"),
                    LVML_ADD_ATTR_FUNC(parse_height, obj,  "height"),
                    LVML_ADD_ATTR_FUNC(parse_margin_height, obj,  "mg_height"),
                    LVML_ADD_ATTR_FUNC(parse_margin_width, obj,  "mg_width"),
                    LVML_ADD_ATTR_FUNC(parse_padding_height, obj,  "pd_height"),
                    LVML_ADD_ATTR_FUNC(parse_padding_width, obj,  "pd_width"),
                    LVML_ADD_ATTR_FUNC(parse_pos_x, obj,  "pos_x"),
                    LVML_ADD_ATTR_FUNC(parse_pos_y, obj,  "pos_y"),
                    LVML_ADD_ATTR_FUNC(parse_hidden, obj,  "hidden"),
            };

            for(const auto& attr : attr_lut) {
                pugi::xml_attribute xml_attr;
                xml_attr = node.attribute(attr.name());
                if (xml_attr) {
                    attr.run(xml_attr, obj);
                }
            }
        }


    private:
        static def::state_t parse_width(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_width(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        };

        static def::state_t parse_height(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_height(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_margin_width(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_width_margin(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_margin_height(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_height_margin(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_padding_height(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_height_fit(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_padding_width(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val != UINT16_MAX) {
                lv_obj_set_width_fit(ui_obj, val);
                return def::STATE_OK;
            } else {
                return def::STATE_INVALID_ATTR;
            }
        }

        static def::state_t parse_pos_x(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val == UINT16_MAX) return def::STATE_INVALID_ATTR;
            lv_obj_set_x(ui_obj, val);
            return def::STATE_OK;
        }

        static def::state_t parse_pos_y(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            uint16_t val = attr.as_uint(UINT16_MAX);
            if (val == UINT16_MAX) return def::STATE_INVALID_ATTR;
            lv_obj_set_y(ui_obj, val);
            return def::STATE_OK;
        }

        static def::state_t parse_hidden(const pugi::xml_attribute &attr, lv_obj_t *ui_obj)
        {
            lv_obj_set_hidden(ui_obj, attr.as_bool(false));
            return def::STATE_OK;
        }
    };
}