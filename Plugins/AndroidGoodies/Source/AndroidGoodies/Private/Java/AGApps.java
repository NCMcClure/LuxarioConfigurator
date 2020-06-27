// Copyright (c) 2018 Nineva Studios

package com.ninevastudios.androidgoodies;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.Uri;
import android.support.annotation.Keep;
import android.support.v4.content.ContextCompat;
import android.util.Log;

import java.io.File;

@Keep
public class AGApps {

	private static final String instagramProfileFormatUri = "http://instagram.com/_u/%s";
	private static final String instagramPackageName = "com.instagram.android";
	private static final String twitterProfileFormatUri = "twitter://user?screen_name=%s";
	private static final String twitterFallbackFormatUri = "https://twitter.com/%s";
	private static final String facebookProfileFormatUri = "fb://profile/%s";
	private static final String facebookFallbackFormatUri = "https://www.facebook.com/%s";
	private static final String packageFormatUri = "package:%s";

	@Keep
	public static void watchYoutubeVideo(Activity activity, String videoId)
	{
		Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse("vnd.youtube:" + videoId));

		try
		{
			activity.startActivity(intent);
		}
		catch (Exception e)
		{
			Intent fallbackIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("http://www.youtube.com/watch?v=" + videoId));
			activity.startActivity(fallbackIntent);
		}
	}

	@Keep
	public static void openInstagramProfile(Activity activity, String profileId)
	{
		openUserProfile(activity, profileId, instagramProfileFormatUri, instagramPackageName, instagramProfileFormatUri);
	}

	@Keep
	public static void openTwitterProfile(Activity activity, String profileId)
	{
		openUserProfile(activity, profileId, twitterProfileFormatUri, "", twitterFallbackFormatUri);
	}

	@Keep
	public static void openFacebookProfile(Activity activity, String profileId)
	{
		openUserProfile(activity, profileId, facebookProfileFormatUri, "", facebookFallbackFormatUri);
	}

	@Keep
	public static void openAnotherApplication(Activity activity, String packageName)
	{
		Intent launchIntent = activity.getPackageManager().getLaunchIntentForPackage(packageName);
		if(launchIntent != null)
		{
			launchIntent.addCategory(Intent.CATEGORY_LAUNCHER);
			activity.startActivity(launchIntent);
		}
		else
		{
			Log.d("AndroidGoodies","The package could not be found");
		}
	}

	@Keep
	public static void uninstallPackage(Activity activity, String packageName)
	{
		activity.startActivity(new Intent(Intent.ACTION_DELETE, Uri.parse(String.format(packageFormatUri, packageName))));
	}

	@Keep
	public static void installApkFromFile(Activity activity, String path)
	{
		try
		{
			Intent intent = new Intent(Intent.ACTION_VIEW, Uri.fromFile(new File(path)))
					.setType("application/vnd.android.package-archive");
			activity.startActivity(intent);
		}
		catch (Exception e)
		{
			Log.d("AndroidGoodies","The file could not be found.");
		}
	}

	@Keep
	public static boolean hasPhoneApp(Activity activity) {
		Intent intent = new Intent(Intent.ACTION_DIAL);
		try {
			intent.resolveActivity(activity.getPackageManager());
			return true;
		} catch (Exception e) {
			return false;
		}
	}

	@Keep
	public static void dialPhoneNumber(Activity activity, String number) {
		Intent intent = new Intent(Intent.ACTION_DIAL);
		intent.setData(uriForNumber(number));
		activity.startActivity(intent);
	}

	@Keep
	public static void callPhoneNumber(Activity activity, String number) {
		if (ContextCompat.checkSelfPermission(activity, Manifest.permission.CALL_PHONE) == PackageManager.PERMISSION_GRANTED) {
			Intent intent = new Intent(Intent.ACTION_CALL);
			intent.setData(uriForNumber(number));
			activity.startActivity(intent);
		}
	}

	private static Uri uriForNumber(String number) {
		return Uri.parse("tel:" + number);
	}

	private static void openUserProfile(Activity activity, String profileId, String formatUri, String packageName, String fallbackFormatUri)
	{
		Intent intent = createOpenProfileIntent(profileId, formatUri);
		if(!packageName.isEmpty())
		{
			intent.setPackage(packageName);
		}
		try
		{
			activity.startActivity(intent);
		}
		catch (Exception e)
		{
			Intent fallbackIntent = createOpenProfileIntent(profileId, fallbackFormatUri);
			activity.startActivity(fallbackIntent);
		}
	}

	private static Intent createOpenProfileIntent(String profileId, String formatUri)
	{
		return new Intent(Intent.ACTION_VIEW, Uri.parse(String.format(formatUri, profileId)));
	}
}
