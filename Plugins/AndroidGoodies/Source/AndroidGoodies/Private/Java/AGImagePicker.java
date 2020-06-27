// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.Build;
import android.os.Environment;
import android.os.Handler;
import android.provider.MediaStore;
import android.support.annotation.Keep;
import android.support.annotation.NonNull;
import android.util.Log;
import android.view.View;

import com.ninevastudios.androidgoodies.pickers.api.CacheLocation;
import com.ninevastudios.androidgoodies.pickers.api.CameraImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.ImagePicker;
import com.ninevastudios.androidgoodies.pickers.api.Picker;
import com.ninevastudios.androidgoodies.pickers.api.callbacks.ImagePickerCallback;
import com.ninevastudios.androidgoodies.pickers.api.entity.ChosenImage;
import com.ninevastudios.androidgoodies.pickers.core.ImagePickerImpl;

import java.io.File;
import java.io.FileOutputStream;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.util.List;

@Keep
public class AGImagePicker {

	@Keep
	public static native void onImageReceived(byte[] buffer, int width, int height);

	@Keep
	public static native void onImageReceiveError(String error);

	public static final String EXTRA_QUALITY = "Quality";
	private static final String EXTRA_MAX_SIZE = "MaximumSize";
	private static final String EXTRA_SHOULD_GENERATE_THUMBNAILS = "ShouldGenerateThumbnails";
	private static final String EXTRAS_PHOTO_OUTPUT_PATH = "EXTRAS_PHOTO_OUTPUT_PATH";
	private static final int UNUSED = -1;

	private static ImagePicker imagePicker;
	private static final String FILE_KEY = "ANDROID_GOODIES_PREFS";

	@Keep
	public static void pickImage(Activity activity, int quality, int maximumSize, boolean shouldGenerateThumbnails) {
		startGoodiesActivity(activity, quality, maximumSize, shouldGenerateThumbnails, Picker.PICK_IMAGE_DEVICE);
	}

	@Keep
	public static void takePhoto(Activity activity, boolean shouldGenerateThumbnails) {
		startGoodiesActivity(activity, UNUSED, UNUSED, shouldGenerateThumbnails, Picker.PICK_IMAGE_CAMERA);
	}

	@SuppressLint("ObsoleteSdkInt")
	@Keep
	public static void saveImageToGallery(Activity activity, byte[] buffer, String fileName, int width, int height)
	{
		Log.d("Goodies", String.valueOf(buffer.length));
		Bitmap bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
		ByteBuffer byteBuffer = ByteBuffer.wrap(buffer);
		bitmap.copyPixelsFromBuffer(byteBuffer);
		//MediaStore.Images.Media.insertImage(activity.getContentResolver(), bitmap ,fileName , "description");
		File root = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES);
		File file = new File(root, fileName + ".png");
		Log.d("Goodies", file.getAbsolutePath());
		try {
			FileOutputStream out = new FileOutputStream(file);
			bitmap.compress(Bitmap.CompressFormat.PNG, 100, out);
			out.flush();
			out.close();
			if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT)
			{
				MediaScannerConnection.scanFile(activity, new String[]{file.toString()}, null,
						new MediaScannerConnection.OnScanCompletedListener() {
							public void onScanCompleted(String path, Uri uri) {
							}
						});
			}
			else {
				Uri uri = Uri.fromFile(file);
				Intent intent = new Intent(Intent.ACTION_MEDIA_MOUNTED, uri);
				activity.sendBroadcast(intent);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

	@Keep
	public static void pickImageInternal(Intent intent, Activity context, int quality) {
		persistImagePickerSettings(intent, context);

		imagePicker = new ImagePicker(context);
		imagePicker.setImagePickerCallback(imagePickerCallback);
		imagePicker.setQuality(quality);
		imagePicker.pickImage();
	}

	@Keep
	public static void pickImageFromCameraInternal(Intent intent, Activity context) {
		CameraImagePicker picker = new CameraImagePicker(context);
		picker.setImagePickerCallback(imagePickerCallback);

		String outputPath = picker.pickImage();
		if (outputPath == null) {
			onImageReceiveError("Taking photo failed");
			return;
		}

		intent.putExtra(EXTRAS_PHOTO_OUTPUT_PATH, outputPath);
		persistImagePickerSettings(intent, context);
	}

	static void handlePhotoReceived(int requestCode, int resultCode, Intent data, AndroidGoodiesActivity activity) {
		if (resultCode != Activity.RESULT_OK) {
			onImageReceiveError("Activity result is not OK.");
			return;
		}

		ImagePickerImpl picker;
		if (requestCode == Picker.PICK_IMAGE_DEVICE) {
			picker = new ImagePicker(activity);
		} else {
			picker = new CameraImagePicker(activity);
		}
		configureImagePicker(activity, picker);
		picker.setCacheLocation(CacheLocation.INTERNAL_APP_DIR);

		picker.setImagePickerCallback(imagePickerCallback);
		picker.submit(data);
	}

	@NonNull
	private static ImagePickerCallback imagePickerCallback = new ImagePickerCallback() {
		@Override
		public void onImagesChosen(List<ChosenImage> images) {
			Log.d("AndroidGoodies", "Inside callback");
			if (images.isEmpty()) {
				onImageReceiveError("Image array is empty.");
				return;
			}

			Log.d("AndroidGoodies", "Array not empty");
			ChosenImage img = images.get(0);
			final int width = img.getWidth();
			final int height = img.getHeight();

			if (img.getWidth() == 0 || img.getHeight() == 0) {
				onImageReceiveError("Image width or height is 0.");
				return;
			}

			Log.d("AndroidGoodies", "Image has height and width");

			String path = img.getOriginalPath();
			if (path.length() == 0) {
				onImageReceiveError("Image path is empty.");
				return;
			}
			Log.d("AndroidGoodies", "Image path is not empty");

			Bitmap bitmap = BitmapFactory.decodeFile(path);
			onImageReceived(getBitmapBytes(bitmap), width, height);
		}

		@Override
		public void onError(String message) {
			onImageReceiveError(message);
		}
	};

	private static void configureImagePicker(Activity activity, ImagePickerImpl picker) {
		int maxSize = getMaxImageSize(activity);
		picker.ensureMaxSize(maxSize, maxSize);
		picker.shouldGenerateThumbnails(shouldGenerateThumbnails(activity));
		picker.reinitialize(getPhotoOutputPath(activity));
	}

	private static int getMaxImageSize(Activity context) {
		return getPrefs(context).getInt(EXTRA_MAX_SIZE, 0);
	}

	private static boolean shouldGenerateThumbnails(Activity activity) {
		return getPrefs(activity).getBoolean(EXTRA_SHOULD_GENERATE_THUMBNAILS, true);
	}

	private static SharedPreferences getPrefs(Activity context) {
		return context.getSharedPreferences(FILE_KEY, Context.MODE_PRIVATE);
	}

	private static String getPhotoOutputPath(Activity context) {
		return getPrefs(context).getString(EXTRAS_PHOTO_OUTPUT_PATH, null);
	}

	@SuppressLint("ApplySharedPref")
	private static void persistImagePickerSettings(Intent data, Activity context) {
		SharedPreferences.Editor editor = getPrefs(context).edit();
		if (data.hasExtra(EXTRA_MAX_SIZE)) {
			int maxSize = data.getIntExtra(EXTRA_MAX_SIZE, 0);
			editor.putInt(EXTRA_MAX_SIZE, maxSize);
		}
		if (data.hasExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS)) {
			boolean genThumbnails = data.getBooleanExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS, true);
			editor.putBoolean(EXTRA_SHOULD_GENERATE_THUMBNAILS, genThumbnails);
		}
		if (data.hasExtra(EXTRAS_PHOTO_OUTPUT_PATH)) {
			String photoOutputPath = data.getStringExtra(EXTRAS_PHOTO_OUTPUT_PATH);
			editor.putString(EXTRAS_PHOTO_OUTPUT_PATH, photoOutputPath);
		}
		editor.commit();
	}

	static byte[] getBitmapBytes(Bitmap bitmap) {
		int width = bitmap.getWidth();
		int height = bitmap.getHeight();
		int[] colors = new int[width * height];
		bitmap.getPixels(colors, 0, width, 0, 0, width, height);

		ByteBuffer byteBuffer = ByteBuffer.allocate(colors.length * 4);
		IntBuffer intBuffer = byteBuffer.asIntBuffer();
		intBuffer.put(colors);
		return byteBuffer.array();
	}

	private static void startGoodiesActivity(Activity activity, int quality, int maximumSize,
	                                         boolean shouldGenerateThumbnails, int pickerType) {
		Intent intent = new Intent(activity, AndroidGoodiesActivity.class);
		if (quality != UNUSED) {
			intent.putExtra(EXTRA_QUALITY, quality);
		}

		if (maximumSize != UNUSED) {
			intent.putExtra(EXTRA_MAX_SIZE, maximumSize);
		}

		intent.putExtra(EXTRA_SHOULD_GENERATE_THUMBNAILS, shouldGenerateThumbnails);
		intent.putExtra(AndroidGoodiesActivity.EXTRAS_PICKER_TYPE, pickerType);
		activity.startActivity(intent);
	}
}
