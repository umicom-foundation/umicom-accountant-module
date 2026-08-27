/*-----------------------------------------------------------------------------
 * Umicom Accountant Module
 * File: src/application.c
 *
 * PURPOSE:
 *   Bind the product identity to the canonical Framework application-experience catalogue.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include "umicom/accountant/application.h"

#include "umicom/application/experience_catalogue.h"

const char *umi_accountant_application_id(void)
{
    return "org.umicom.accountant";
}

const UmiApplicationExperienceDefinition *
umi_accountant_application_experience(void)
{
    return umi_application_experience_catalogue_find(
        umi_accountant_application_id());
}

UmiStatus umi_accountant_application_status(
    UmiApplicationExperienceStatus *out_status)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_accountant_application_experience();
    if (definition == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_experience_status(definition, out_status);
}
