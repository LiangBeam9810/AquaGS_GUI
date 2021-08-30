#include "blup.h"

void blup_Init(blup blup_input)
{
    blup_input.fiexd_effect_listwidget->addItems(blup_input.fixed_effect_list);
    blup_input.random_effect_listwidget->addItems(blup_input.random_effect_list);

}

void blup_fold_validate_Init(fold_validate fold_validate_input)
{
    fold_validate_input.k_flod_times_ComboBox->setEnabled(false);

}
