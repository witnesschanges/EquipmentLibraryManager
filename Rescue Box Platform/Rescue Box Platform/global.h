#pragma once

#include "stdafx.h"

#include <ProMenuBar.h>
#include <ProAsmcomp.h>
#include <ProModelitem.h>
#include <ProSolid.h>
#include "ProUtil.h"

extern CString m_equLibPath;
extern CString m_mechLibPath;

extern int InsertEquipment(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data);
extern uiCmdAccessState InsertEquipmentAccess(uiCmdAccessMode access_mode);

extern int InsertMechanism(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data);
extern uiCmdAccessState InsertMechanismAccess(uiCmdAccessMode access_mode);

extern int EditMechanism(uiCmdCmdId  command, uiCmdValue *p_value, void *p_push_command_data);
extern uiCmdAccessState EditMechanismAccess(uiCmdAccessMode access_mode);