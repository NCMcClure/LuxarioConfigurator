// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies.pickers.api.callbacks;

import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenAudio;

import java.util.List;

public interface AudioPickerCallback extends PickerCallback {
    void onAudiosChosen(List<ChosenAudio> audios);
}
