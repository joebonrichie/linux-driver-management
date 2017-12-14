/*
 * This file is part of linux-driver-management.
 *
 * Copyright © 2016-2017 Ikey Doherty
 *
 * linux-driver-management is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#define _GNU_SOURCE

#include "gpu-config.h"
#include "util.h"

struct _LdmGPUConfigClass {
        GObjectClass parent_class;
};

/**
 * LdmGPUConfig
 *
 * This object is used to query an #LdmManager for the system GPU configuration
 * and topology. Using the #LdmGPUConfig allows end-users to query exactly
 * what kind of configuration is present, and determine the primary vs secondary
 * GPUs, presence of Optimus/Hybrid GPUs, etc.
 */
struct _LdmGPUConfig {
        GObject parent;

        LdmManager *manager;

        guint n_gpu; /* How many GPUs we got? */
};

static void ldm_gpu_config_set_property(GObject *object, guint id, const GValue *value,
                                        GParamSpec *spec);
static void ldm_gpu_config_get_property(GObject *object, guint id, GValue *value, GParamSpec *spec);
static void ldm_gpu_config_constructed(GObject *obj);
static void ldm_gpu_config_analyze(LdmGPUConfig *self);

G_DEFINE_TYPE(LdmGPUConfig, ldm_gpu_config, G_TYPE_OBJECT)

/* Property IDs */
enum { PROP_MANAGER = 1, N_PROPS };

static GParamSpec *obj_properties[N_PROPS] = {
        NULL,
};

/**
 * ldm_gpu_config_dispose:
 *
 * Clean up a LdmGPUConfig instance
 */
static void ldm_gpu_config_dispose(GObject *obj)
{
        G_OBJECT_CLASS(ldm_gpu_config_parent_class)->dispose(obj);
}

/**
 * ldm_gpu_config_class_init:
 *
 * Handle class initialisation
 */
static void ldm_gpu_config_class_init(LdmGPUConfigClass *klazz)
{
        GObjectClass *obj_class = G_OBJECT_CLASS(klazz);

        /* gobject vtable hookup */
        obj_class->constructed = ldm_gpu_config_constructed;
        obj_class->dispose = ldm_gpu_config_dispose;
        obj_class->get_property = ldm_gpu_config_get_property;
        obj_class->set_property = ldm_gpu_config_set_property;

        /**
         * LdmGPUConfig:manager: (type LdmManager) (transfer none)
         *
         * Parent device for this device instance
         */
        obj_properties[PROP_MANAGER] =
            g_param_spec_pointer("manager",
                                 "LdmManager",
                                 "Manager for our instance",
                                 G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

        g_object_class_install_properties(obj_class, N_PROPS, obj_properties);
}

static void ldm_gpu_config_set_property(GObject *object, guint id, const GValue *value,
                                        GParamSpec *spec)
{
        LdmGPUConfig *self = LDM_GPU_CONFIG(object);

        switch (id) {
        case PROP_MANAGER:
                self->manager = g_value_get_pointer(value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

static void ldm_gpu_config_get_property(GObject *object, guint id, GValue *value, GParamSpec *spec)
{
        LdmGPUConfig *self = LDM_GPU_CONFIG(object);

        switch (id) {
        case PROP_MANAGER:
                g_value_set_pointer(value, self->manager);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID(object, id, spec);
                break;
        }
}

/**
 * ldm_gpu_config_constructed:
 *
 * We're now up and running with a valid Manager instance, probe it and
 * find out exactly what our state looks like. :)
 */
static void ldm_gpu_config_constructed(GObject *obj)
{
        ldm_gpu_config_analyze(LDM_GPU_CONFIG(obj));
        G_OBJECT_CLASS(ldm_gpu_config_parent_class)->constructed(obj);
}

/**
 * ldm_gpu_config_init:
 *
 * Handle construction of the LdmGPUConfig
 */
static void ldm_gpu_config_init(LdmGPUConfig *self)
{
        self->n_gpu = 0;
}

/**
 * ldm_gpu_config_analyze:
 *
 * Ask the manager what the story is.
 */
static void ldm_gpu_config_analyze(__ldm_unused__ LdmGPUConfig *self)
{
        g_autoptr(GList) devices = NULL;

        devices = ldm_manager_get_devices(self->manager, LDM_DEVICE_TYPE_PCI | LDM_DEVICE_TYPE_GPU);
        if (!devices) {
                g_message("failed to discover any GPUs");
                return;
        }

        self->n_gpu = g_list_length(devices);
        g_message("not yet fully implemented!");
}

/**
 * ldm_gpu_config_new:
 * @manager: (transfer none): Manager to query for a GPU config
 *
 * Construct a GPU configuration from the #LdmManager to determine the
 * exact GPU topology.
 */
LdmGPUConfig *ldm_gpu_config_new(LdmManager *manager)
{
        g_assert(manager != NULL);

        return g_object_new(LDM_TYPE_GPU_CONFIG, "manager", manager, NULL);
}

/**
 * ldm_gpu_config_get_manager:
 *
 * Returns: (transfer none): A reference to our manager
 */
LdmManager *ldm_gpu_config_get_manager(LdmGPUConfig *self)
{
        g_return_val_if_fail(self != NULL, NULL);

        return self->manager;
}

/**
 * ldm_gpu_config_count:
 *
 * Determine the number of GPUs present on the system
 *
 * Returns: Number of GPUs
 */
guint ldm_gpu_config_count(LdmGPUConfig *self)
{
        g_return_val_if_fail(self != NULL, 0);
        return self->n_gpu;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
