// Copyright (c) 2019 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.Camera;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraManager;
import android.media.AudioAttributes;
import android.os.BatteryManager;
import android.os.Build;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.support.annotation.Keep;
import android.util.Log;

@Keep
public class AGHardware {
	private static Camera _camera;

	@Keep
	public static void enableFlashlight(Activity activity, final boolean enable) {

		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
			enableFlashlightNew(activity, enable);
		} else {
			enableFlashlightOld(activity, enable);
		}
	}

	@Keep
	public static boolean hasVibrator(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		return vibrator != null && vibrator.hasVibrator();
	}

	@Keep
	public static boolean hasAmplitudeControl(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		return vibrator != null && Build.VERSION.SDK_INT >= Build.VERSION_CODES.O && vibrator.hasAmplitudeControl();
	}

	@Keep
	public static void vibrate(Activity activity, final long duration) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.vibrate(duration);
		}
	}

	@Keep
	public static void vibrate(Activity activity, final long[] intervals, final int repeat) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.vibrate(intervals, repeat);
		}
	}

	@TargetApi(Build.VERSION_CODES.O)
	@Keep
	public static void vibrate(Activity activity, VibrationEffect effect) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null && effect != null) {
			vibrator.vibrate(effect);
		}
	}

	@TargetApi(Build.VERSION_CODES.O)
	@Keep
	public static void vibrate(Activity activity, VibrationEffect effect, final int flags, final int usage, final int contentType) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null && effect != null) {
			vibrator.vibrate(effect,
					new AudioAttributes.Builder()
					.setUsage(usage)
					.setFlags(flags)
					.setContentType(contentType)
					.build());
		}
	}

	@Keep
	public static void stopVibration(Activity activity) {
		Vibrator vibrator = (Vibrator) activity.getSystemService(Context.VIBRATOR_SERVICE);
		if (vibrator != null) {
			vibrator.cancel();
		}
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long duration, final int amplitude) {
		Log.d("AndroidGoodies", String.valueOf(amplitude));
		return VibrationEffect.createOneShot(duration, amplitude);
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long[] durations, final int amplitude) {
		return VibrationEffect.createWaveform(durations, amplitude);
	}

	@Keep
	@TargetApi(Build.VERSION_CODES.O)
	public static VibrationEffect createVibrationEffect(final long[] durations, int[] amplitudes, final int repeat) {
		return VibrationEffect.createWaveform(durations, amplitudes, repeat);
	}

	@Keep
	public static long computeRemainingChargeTime(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);

			long result = manager != null ? manager.computeChargeTimeRemaining() : -1;
			Log.d("AndroidGoodies", String.valueOf(result));
			return result;
		}

		return -1;
	}

	@Keep
	public static int getBatteryCapacity(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CAPACITY) : -1;
		}

		return -1;
	}

	@Keep
	public static int getBatteryChargeCounter(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) : -1;
		}

		return -1;
	}

	@Keep
	public static int getAverageBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_AVERAGE) : -1;
		}

		return -1;
	}

	@Keep
	public static int getImmediateBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_NOW) : -1;
		}

		return -1;
	}

	@Keep
	public static int getBatteryCurrent(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			return manager != null ? manager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CURRENT_NOW) : -1;
		}

		return -1;
	}

	@Keep
	public static long getBatteryEnergyCounter(Activity activity) {
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
			BatteryManager manager = (BatteryManager) activity.getSystemService(Context.BATTERY_SERVICE);
			long result = manager != null ? manager.getLongProperty(BatteryManager.BATTERY_PROPERTY_ENERGY_COUNTER) : -1;
			result = result == Long.MIN_VALUE ? - 1 : result;
			Log.d("AndroidGoodies", String.valueOf(result));
			return result;
		}

		return -1;
	}

	@Keep
	public static int getBatteryStatus(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return BatteryManager.BATTERY_STATUS_UNKNOWN;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_STATUS, BatteryManager.BATTERY_STATUS_UNKNOWN);
	}

	@TargetApi(Build.VERSION_CODES.P)
	@Keep
	public static boolean isBatteryLow(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return false;
		}

		return batteryIntent.getBooleanExtra(BatteryManager.EXTRA_BATTERY_LOW, false);
	}

	@Keep
	public static int getBatteryHealth(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return BatteryManager.BATTERY_HEALTH_UNKNOWN;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_HEALTH, BatteryManager.BATTERY_HEALTH_UNKNOWN);
	}

	@Keep
	public static int getBatteryLevel(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return -1;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
	}

	@Keep
	public static int getBatteryPluggedState(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return 0;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_PLUGGED, 0);
	}

	@Keep
	public static boolean isBatteryPresent(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return false;
		}

		return batteryIntent.getBooleanExtra(BatteryManager.EXTRA_PRESENT, false);
	}

	@Keep
	public static int getBatteryScale(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return -1;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_SCALE, -1);
	}

	@Keep
	public static String getBatteryTechnology(Activity activity) {
		String unknownString = "Unknown";

		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return unknownString;
		}

		String result = batteryIntent.getStringExtra(BatteryManager.EXTRA_TECHNOLOGY);
		return result == null ? unknownString : result;
	}

	@Keep
	public static int getBatteryTemperature(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return Integer.MIN_VALUE;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_TEMPERATURE, Integer.MIN_VALUE);
	}

	@Keep
	public static int getBatteryVoltage(Activity activity) {
		IntentFilter filter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
		Intent batteryIntent = activity.registerReceiver(null, filter);
		if(batteryIntent == null) {
			return 0;
		}

		return batteryIntent.getIntExtra(BatteryManager.EXTRA_VOLTAGE, 0);
	}

	private static void enableFlashlightOld(Activity activity, final boolean enable) {
		try {
			activity.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					if (enable) {
						_camera = Camera.open();
						Camera.Parameters cameraParameters = _camera.getParameters();
						cameraParameters.setFlashMode(Camera.Parameters.FLASH_MODE_ON);
						_camera.setParameters(cameraParameters);
						_camera.startPreview();
					} else {
						if (_camera != null) {
							_camera.stopPreview();
							_camera.release();
							_camera = null;
						}
					}
				}
			});
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@TargetApi(Build.VERSION_CODES.M)
	private static void enableFlashlightNew(Activity activity, final boolean enable) {
		try {
			CameraManager cameraManager = (CameraManager) activity.getSystemService(Context.CAMERA_SERVICE);
			if (cameraManager != null) {
				String cameraId = cameraManager.getCameraIdList()[0];
				cameraManager.setTorchMode(cameraId, enable);
			} else {
				Log.d("AndroidGoodies", "enableFlashlight: could not get camera manager");
			}
		} catch (CameraAccessException e) {
			e.printStackTrace();
		}
	}
}
