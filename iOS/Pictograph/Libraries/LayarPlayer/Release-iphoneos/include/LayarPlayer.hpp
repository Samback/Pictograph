/**
 * @file LayarPlayer.hpp
 * @brief Main include file of the LayarPlayer SDK
 *
 * Include this file to include all public header files of the LayarPlayer SDK
 * By implamenting the LayarPlayer in your application, you agree to the Terms and Conditions described in the Layar_Software_Development_Kit_License_Agreement.pdf
 * file which can be found in the LayarPlayer documentation folder
 *
 * @authors Lawrence Lee and Dirk Groten, Layar B.V.
 * @date 5 January 2011
 */

#import "LPViewControllerBase.h"
#import "LPAugmentedRealityViewController.hpp"
#import "LayarPlayerDelegate.h"

/**
 * @mainpage LayarPlayer SDK Documentation v2.0
 *
 * @section introduction Introduction
 *
 * The LayarPlayer SDK is a static library that implements the core functionality of Layar. Using the LayarPlayer SDK it is
 * possible to load a layer and present the Augmented Reality view to the user. The LayarPlayer SDK will start all necessary
 * services such as location management and device motion control.
 *
 * @section minimumrequirements Minimum requirements
 *
 * The LayarPlayer SDK requires a minimum installed iOS version of 4.3, and that the device capabilities include OpenGL ES 2 support,
 * location support, a camera, magnetometer and an accelerometer. The LayarPlayer SDK is also built for ARM7 architecture.
 * The application in which the LayarPlayer SDK is used should reflect this by specifying the folowing values
 * in the applications .plist for the key UIRequiredDeviceCapabilities:
 *
 * @li opengles-2
 * @li video-camera
 * @li accelerometer
 * @li magnetometer
 * @li location-services
 * @li armv7
 *
 * @section projectconfiguration Project configuration
 *
 * Any project using the LayarPlayer SDK must have the "Minimum OS Version" set to 4.3. It must also specify "Architectures" to armv7.
 * Additionally, it must include the following Frameworks:
 *
 * @li AudioToolbox
 * @li AVFoundation
 * @li CFNetwork
 * @li CoreData
 * @li CoreGraphics
 * @li CoreLocation
 * @li CoreMedia
 * @li CoreMotion
 * @li CoreTelephony
 * @li CoreVideo
 * @li Foundation
 * @li MapKit
 * @li MediaPlayer
 * @li OpenGLES
 * @li QuartzCore
 * @li UIKit
 * @li Security
 * @li SystemConfiguration
 *
 * Add the PlayerLocalization.bundle file to your project, e.g. in the "Supporting Files" group (a group that XCode 4.2 automatically creates when you create a new project).
 *
 * @subsection externallibs External Libraries
 *
 * The LayarPlayer SDK uses some external open source libraries that you might want to use in your own project. In order to avoid symbol conflicts, we're distributing the libraries as separate static libraries together with the LayarPlayer SDK. You need to link you project against the binary static libraries (see Build Configuration section below).
 *
 * If you use the libraries in your application, you'll need to include the path to the header files in the "Header search paths" of your project's build configuration. 
 *
 * You may want to use newer versions of these libraries, in such case make sure you link against compiled static libraries. As long as backward compatibility is maintained, it should work, but Layar makes no guarantees if a different version is used. The two libraries are:
 *
 *
 * @li json-framework by Stig Brautaset: https://github.com/stig/json-framework (v3.0.4 rev 87a86811ba)
 * @li MPOAuthConnection by Karl Adam: https://github.com/thekarladam/MPOAuth (rev 1609e85)
 *
 * All other open-source libraries we use should be obfuscated or consist of header files only, so they shouldn't lead to conflicts. If nevertheless you hit a conflict just let us know and we'll send you the relevant header files.
 *
 *
 * @subsubsection armv7 Armv7 Build Configuration
 *
 * When building the application the following steps must be taken to ensure that the project links against the "liblayarplayer.a" static library. The instructions below were made using XCode 4.2 (4C199 or 4D199).
 *
 * The project settings should have the following changes made:
 *
 * @li The "Architectures" option set to "Standard (armv7)"
 * @li The "Valid Architectures" option should only contain "armv7"
 * @li The "Compiler for C/C++/Objective-C" option should be set to "Apple LLVM Compiler 3.0"
 $ @li The "Base SDK" option should be set to "iOS 5.0"
 * @li The "iOS Deployment Target" option should be set to "iOS 4.3"
 * @li The "Header search paths" option must point to the location of the "include" directory contained by the SDK, e.g. "${PROJECT_DIR}/Libraries/LayarPlayer/${BUILD_STYLE}-${PLATFORM_NAME}/include"
 * @li If you wish to use the "#import <...>" import directive, you must ensure that the "Always search user paths" option is enabled
 * @li The "Library search paths" option must point to the directory containing the relevant Debug or Release version of the "liblayerplayer.a" static library, depending on the build configuration. For example "${PROJECT_DIR}/Libraries/LayarPlayer/${BUILD_STYLE}-${PLATFORM_NAME}".
 * @li The "Library search paths" option must also point to the directories containing the static libraries for json-framework and MPOAuth, e.g. "${PROJECT_DIR}/Libraries/stig-json-framework/build/${BUILD_STYLE}-${PLATFORM_NAME}" and "${PROJECT_DIR}/Libraries/thekarladam-MPOAuth/build/${BUILD_STYLE}-${PLATFORM_NAME}". Note: If your project already includes these libraries, you can skip this step.
 * @li The "Other linker flags" option must contain the flags @c -llayarplayer @c -lsbjson-ios @c -lMPOAuthMobile @c -lxml2 @c -lz @c -ObjC. Just copy and paste the flags mentioned here into the field in XCode: before pasting, select the line with "Other C Flags" to highlight it, then click once on the value field to turn it into an editable text field where you can paste into. Do not paste when the row is selected (no text field to edit) or if the dialog opens where each field is listed individually, that will mess things up. Note: If your project already contains @c libsbjson-ios or @c libMPOAuthMobile, you don't need to include them here.
 * @li The "Other C Flags" option should contain the following flags: -DNS_BLOCK_ASSERTIONS=1 -DEIGEN_DONT_VECTORIZE -DEIGEN_NO_DEBUG -fblocks -ffunction-sections -funwind-tables -fomit-frame-pointer -fno-strict-aliasing -finline-limit=64 -finline-functions -fno-math-errno -funsafe-math-optimizations -fno-trapping-math -fno-rounding-math -fno-signaling-nans -fcx-limited-range -frename-registers -ftracer. Just copy and paste the flags mentioned here into the field in XCode: before pasting, select the line with "Other C Flags" to highlight it, then click once on the value field to turn it into an editable text field where you can paste into. Do not paste when the row is selected (no text field to edit) or if the dialog opens where each field is listed individually, that will mess things up. 
 *
 
 * @section usage Usage
 *
 * In order to use the LayarPlayer SDK in an application, you need to import the LayarPlayer.hpp in the class file that will launch the LayarPlayer. Note that since it's an Objective-C++
 * header file, you'll need to change any file that imports it into an Objective-C++ file as well (e.g. MyViewController.mm would import LayarPlayer.hpp, so 
 * MyViewController.hpp is the corresponding header file). In practice, all view controllers in the hierarchy above MyViewController, the AppDelegate,
 * and main will need to be renamed as (Objective-)C++ files.
 
 * When you wish to launch the
 * Layar Augmented Reality view, initialize an instance of the @c LPAugmentedRealityViewController. It is imperative that you present the
 * LPAugmentedRealityViewController modally in order for it to function correctly.
 * Once you have presented the Augmented Reality View, call the @c loadLayerWithName: method with the name of the layer that you wish to load
 * as its argument. The LayarPlayer SDK will manage the loading of the layer as well as all POIs and their resources.
 * The LayerPlayer also supports backgrounding, and will pause all OpenGL rendering as well as relenquishing all device hardware usage.
 *
* @subsection example Example
 *
 * The following code snippet can be used to present an Augmented Reality View and load a layer:
 *
 * @code
 * #import <LayarPlayer.hpp>
 * ...
 * NSString *layerName = ...;
 * NSString *consumerKey = ...;
 * NSString *consumerSecret = ...;
 *
 * NSArray *oauthKeys = [NSArray arrayWithObjects:LPConsumerKeyParameterKey, LPConsumerSecretParameterKey, nil];
 * NSArray *oauthValues = [NSArray arrayWithObjects:consumerKey, consumerSecret, nil];
 * NSDictionary *oauthParameters = [NSDictionary dictionaryWithObjects:oauthValues forKeys:oauthKeys];
 *
 * NSArray *layerKeys = [NSArray arrayWithObject:@"radius"];
 * NSArray *layerValues = [NSArray arrayWithObject:@"1000"];
 * NSDictionary *layerFilters = [NSDictionary dictionaryWithObjects:layerValues forKeys:layerKeys];
 *
 * LPAugmentedRealityViewController *augmentedRealityViewController = [[[LPAugmentedRealityViewController alloc] init] autorelease];
 * augmentedRealityViewController.delegate = self;
 * [self presentModalViewController:augmentedRealityViewController animated:YES];
 * [augmentedRealityViewController loadLayerWithName:layerName oauthParameters:oauthParameters parameters:layerFilters options:LPMapViewDisabled | LPListViewDisabled];
 * @endcode
 *
 * The above example disables the menu options for the user to navigate to the map and list views. Use the default option @c LPAllViewsEnabled to enable navigation to all views.
 *
 * @subsubsection oauth OAuth signing
 *
 * All requests made by the LayarPlayer need have a valid OAuth key and secret sent with them in order to successfully pass authentication checks by the Layar server.
 * This information is specific to each layer, and must be configured for the layer at http://www.layar.com/publishing/#layers
 *
 * @subsubsection delegatemethods Delegate methods
 *
 * By implementing the @c LayarPlayerDelegate protocol a program can receive events from the LayarPlayer. Currently two close events are sent when the user exits the program by
 * clicking the "Close" button in one of the views. If the program that calls the LayarPlayer implements the @c layarPlayerWillClose and the @c layarPlayerDidClose methods these will
 * be called before and after the program exits, respectively.
 *
 * @section launchingfromopenglapp Launching the LayarPlayer from OpenGL applications
 *
 * Extra attention must be paid to resource management when launching the LayarPlayer from an application that makes use of OpenGL to render content. The LayarPlayer is a resource
 * intensive application, and to avoid spawning memory warnings on the device it is running on, any application launching the LayarPlayer should free up as many resources as possible.
 * For OpenGL applications this means that all texture resources should be deleted, and if possible any framebuffers that are in use. Any OpenGL timers or display links should be paused
 * as well. By implementing the delegate methods and assigning a suitable delegate class, the application can rebind its resources when the LayarPlayer closes. Care should be taken to
 * set the application's own OpenGL context when doing so. More information on OpenGL context switching can be found here:
 * http://developer.apple.com/library/ios/#documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/WorkingwithOpenGLESContexts/WorkingwithOpenGLESContexts.html
 */