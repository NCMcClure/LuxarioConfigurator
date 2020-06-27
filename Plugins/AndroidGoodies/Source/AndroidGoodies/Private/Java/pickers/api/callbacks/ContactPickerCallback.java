// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenContact;

public interface ContactPickerCallback extends PickerCallback {
    void onContactChosen(ChosenContact contact);
}
