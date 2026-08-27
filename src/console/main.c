/*-----------------------------------------------------------------------------
 * Umicom Accountant Module
 * File: src/console/main.c
 *
 * PURPOSE:
 *   Provide a native verification frontend for the thin product composition.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>

#include "umicom/accountant/application.h"
#include "umicom/accountant/workspace.h"

int main(void)
{
    UmiApplicationExperienceStatus status;
    const UmiApplicationExperienceDefinition *definition =
        umi_accountant_application_experience();
    const UmiExperienceLayoutDefinition *layout =
        umi_accountant_workspace_default();
    const UmiExperienceFeatureDefinition *next =
        umi_accountant_workspace_next_feature();

    if (definition == NULL ||
        umi_accountant_application_status(&status) != UMI_STATUS_OK ||
        layout == NULL) {
        fputs("Umicom Accountant: Framework experience unavailable\n", stderr);
        return 1;
    }

    printf("%s\n", definition->display_name);
    printf("application: %s\n", definition->application_id);
    printf("default layout: %s\n", layout->title);
    printf("panels: %zu\n", status.panel_count);
    printf("layouts: %zu\n", status.layout_count);
    printf("features: %zu\n", status.feature_count);
    printf("readiness: %u%%\n", status.readiness_percent);
    if (next != NULL)
        printf("next: %s [%s]\n", next->title,
               umi_experience_priority_text(next->priority));
    return 0;
}
