#import <Foundation/Foundation.h>

#define DECLARE_KEY(key) extern NSString* const key

DECLARE_KEY(kPrefKeyTransferRules); // NSData (Archived NSArray of PCPredicateGroups)

// upload permission dict keys ***************************************************

DECLARE_KEY(kPrefKeyUploadPermissionsMap); // NSArray of NSDictionaries with keys: extension, enabled, FTPPermissions, S3Permissions, WebDAVPermissions 

DECLARE_KEY(PCPrefKeyDefaultFile);		// NSString - Also defined in FTPKit
DECLARE_KEY(PCPrefKeyDefaultFolder);	// NSString - Also defined in FTPKit
DECLARE_KEY(PCPrefKeyFTPPermissions);	// NSNumber (octal)
DECLARE_KEY(PCPrefKeyS3Permissions);	// NSNumber (octal)
DECLARE_KEY(PCPrefKeyWebDAVPermissions);	// NSNumber (octal)
DECLARE_KEY(PCPrefKeyEnabled);			// NSNumber (bool)
DECLARE_KEY(PCPrefKeyExtension);		// NSString

//proxies
DECLARE_KEY(kPrefKeyProxyServer);	// NSString
DECLARE_KEY(kPrefKeyProxyPort);	// NSNumber (unsigned)
DECLARE_KEY(kPrefKeyProxyType);	// NSNumber (unsigned) defined in ncftp.h as kFirewall*
DECLARE_KEY(kPrefKeyProxyUser);	// NSString

//misc pref keys *****************************************************************

DECLARE_KEY(PCPrefKeyKeepIdleConnectionsAlive);		// NSNumber (bool)
DECLARE_KEY(kPrefKeyUseVerboseLogging);				// NSNumber (bool)
DECLARE_KEY(PCPrefKeyContentExpirationInterval);	// NSNumber (double)
DECLARE_KEY(PCPrefKeyActivityBarVisible);			// NSNumber (bool)
DECLARE_KEY(PCPrefKeyShowHiddenFiles);				// NSNumber (bool)

// advanced server specific prefs dict keys **************************************

DECLARE_KEY(kPrefKeyServerSpecificPrefs);

DECLARE_KEY(kServerPrefKeyAllowsDSStoreUpload);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyConnectionTimeout);	// NSNumber (int)
DECLARE_KEY(kServerPrefKeyParserNameDateSpacing);	// NSNumber (int)
DECLARE_KEY(kServerPrefKeyMachineType);	// NSNumber (int), see ServerTypes.h for enumeration
DECLARE_KEY(kServerPrefKeyRemoteHost);	// NSString
DECLARE_KEY(kServerPrefKeyUseFEATCommand);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyUseMLSTCommand);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyUseCCCCommand);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyUsePRETCommand);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyKeepTransferConnectionsAlive);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyStringEncoding);	// NSNumber (NSUInteger)
DECLARE_KEY(kServerPrefKeyMaximumConnections);	// NSNumber (unsigned)
DECLARE_KEY(kServerPrefKeyRedialDelay);	// NSNumber (int)
DECLARE_KEY(kServerPrefKeyPreserveModificationDates);	// NSNumber (bool)
DECLARE_KEY(kServerPrefKeyMaximumTransferConnections);		// NSNumber (unsigned)
DECLARE_KEY(kServerPrefKeyUseTLSv12); // NSNumber (bool)
DECLARE_KEY(kServerPrefKeyCharacterCompositionType); // NSNumber (int)

DECLARE_KEY(kServerPrefValueServerSpecificDefaultHost);

// transfers pref keys ***********************************************************

DECLARE_KEY(PCPrefKeyAsciiFileTypes);					/* NSArray */
DECLARE_KEY(PCPrefKeyDownloadConflictMode);				/* NSNumber (unsigned short) */
DECLARE_KEY(PCPrefKeyUploadConflictMode);				/* NSNumber (unsigned short) */
DECLARE_KEY(PCPrefKeyTransferSoundPath);				/* NSString */
DECLARE_KEY(PCPrefKeyTransferSoundEnabled);				// NSNumber (bool)
DECLARE_KEY(PCPrefKeySimultaneousTransferLimit);		// NSNumber (integer)
DECLARE_KEY(PCPrefKeyLimitUploadBandwidth);				// NSNumber (bool)
DECLARE_KEY(PCPrefKeyLimitDownloadBandwidth);			// NSNumber (bool)
DECLARE_KEY(PCPrefKeyMaximumUploadKBytesPerSecond);		// NSNumber (double)
DECLARE_KEY(PCPrefKeyMaximumDownloadKBytesPerSecond);	// NSNumber (double)
DECLARE_KEY(PCPrefKeyUsePassiveMode);					// NSNumber (bool)
DECLARE_KEY(PCPrefKeyRemoveQueueTransfersOnCompletion);  // NSNumber (bool)
DECLARE_KEY(kPrefKeyAskBeforeDelete);                   // NSNumber (bool)


#undef DECLARE_KEY
