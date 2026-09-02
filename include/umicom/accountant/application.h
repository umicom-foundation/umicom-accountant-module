/*-----------------------------------------------------------------------------
 * Umicom Accountant Module
 * File: include/umicom/accountant/application.h
 *
 * PURPOSE:
 *   Expose the thin application composition over Framework-owned experience metadata and services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_ACCOUNTANT_APPLICATION_H
#define UMICOM_ACCOUNTANT_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_ACCOUNTANT_MODULE_API_VERSION 1U

/**
 * Provide the accountant application id operation used by this module and its client
 * applications.
 */
const char *umi_accountant_application_id(void);

/**
 * Provide the accountant application experience operation used by this module and its
 * client applications.
 */
const UmiApplicationExperienceDefinition *
umi_accountant_application_experience(void);

/**
 * Provide the accountant application status operation used by this module and its client
 * applications.
 */
UmiStatus umi_accountant_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif

#endif
