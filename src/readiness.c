/*-----------------------------------------------------------------------------
 * Umicom Accountant Module
 * File: src/readiness.c
 *
 * PURPOSE:
 *   Project the canonical Framework feature backlog without product-local roadmap duplication.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/


#include "umicom/accountant/readiness.h"

#include "umicom/accountant/runtime.h"
#include "umicom/application/experience_plan.h"

UmiStatus umi_accountant_readiness_report(
    UmiApplicationReadinessReport *out_report)
{
    const UmiApplicationExperienceDefinition *experience =
        umi_accountant_runtime_experience();
    if (experience == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_readiness_report(experience, out_report);
}

const UmiExperienceFeatureDefinition *umi_accountant_readiness_next_feature(void)
{
    return umi_application_experience_next_feature(
        umi_accountant_runtime_experience());
}
