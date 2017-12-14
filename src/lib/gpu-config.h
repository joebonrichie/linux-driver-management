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

#pragma once

#include <glib-object.h>
#include <manager.h>

G_BEGIN_DECLS

typedef struct _LdmGPUConfig LdmGPUConfig;
typedef struct _LdmGPUConfigClass LdmGPUConfigClass;

#define LDM_TYPE_GPU_CONFIG ldm_gpu_config_get_type()
#define LDM_GPU_CONFIG(o) (G_TYPE_CHECK_INSTANCE_CAST((o), LDM_TYPE_GPU_CONFIG, LdmGPUConfig))
#define LDM_IS_GPU_CONFIG(o) (G_TYPE_CHECK_INSTANCE_TYPE((o), LDM_TYPE_GPU_CONFIG))
#define LDM_GPU_CONFIG_CLASS(o)                                                                    \
        (G_TYPE_CHECK_CLASS_CAST((o), LDM_TYPE_GPU_CONFIG, LdmGPUConfigClass))
#define LDM_IS_GPU_CONFIG_CLASS(o) (G_TYPE_CHECK_CLASS_TYPE((o), LDM_TYPE_GPU_CONFIG))
#define LDM_GPU_CONFIG_GET_CLASS(o)                                                                \
        (G_TYPE_INSTANCE_GET_CLASS((o), LDM_TYPE_GPU_CONFIG, LdmGPUConfigClass))

GType ldm_gpu_config_get_type(void);

/* API */
LdmGPUConfig *ldm_gpu_config_new(LdmManager *manager);
LdmManager *ldm_gpu_config_get_manager(LdmGPUConfig *config);
guint ldm_gpu_config_count(LdmGPUConfig *config);

G_DEFINE_AUTOPTR_CLEANUP_FUNC(LdmGPUConfig, g_object_unref)

G_END_DECLS

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
