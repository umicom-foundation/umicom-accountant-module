/*-----------------------------------------------------------------------------
 * Umicom Accountant Module
 * File: include/umicom/accountant/workspace.h
 *
 * PURPOSE:
 *   Expose product workspace lookups without duplicating Framework workbench or layout logic.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_ACCOUNTANT_WORKSPACE_H
#define UMICOM_ACCOUNTANT_WORKSPACE_H

#include <stddef.h>

#include "umicom/application/experience.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Return the number of records represented by accountant workspace layout without changing
 * their state.
 */
size_t umi_accountant_workspace_layout_count(void);

/**
 * Find accountant workspace layout while leaving the underlying catalogue or model owned
 * by this module.
 */
const UmiExperienceLayoutDefinition *umi_accountant_workspace_layout_at(
    size_t index);

/**
 * Provide the accountant workspace default operation used by this module and its client
 * applications.
 */
const UmiExperienceLayoutDefinition *umi_accountant_workspace_default(void);

/**
 * Provide the accountant workspace next feature operation used by this module and its
 * client applications.
 */
const UmiExperienceFeatureDefinition *umi_accountant_workspace_next_feature(
    void);

#ifdef __cplusplus
}
#endif

#endif
