/**
 * @file LSConstants.h
 * @brief Defines and types
 *
 * This file contains the contants and type definitions used by the SDK
 * @author Lawrence Lee, Layar B.V.
 * @date 14th January 2010
 */

//System imports
#import <Foundation/Foundation.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

/**
 * @brief The API version
 */
#define LSLayarAPIVersion @"6.0"

/**
 * @brief The API version parameter key
 */
#define LSLayarAPIVersionParameterKey	@"version"

/**
 * @brief The maximum amount of POIs a GetPOI response should return
 */
#define LSMaxPOIsInResponse 50

/**
 * @brief The maximum amount of POIs a GetPOI request should ask for using paging
 */
#define LSMaxPOIsForRequest 10

/**
 * @brief The maximum amount of POIs a GetPOI request should ask for using paging
 */
#define LSMaxPOIs 50

/**
 * @brief The maximum size that the cache is allowed to grow to
 * @see LSRenderableCache
 */
#define LSMaxCacheSize 5.0f * 1024.0f * 1024.0f // 5mb

/**
 * @brief The size of a default CIW billboard. (In OpenGL units)
 */
#define LSDefaultBillboardSize 36

/**
 * @brief The centre size of a default CIW billboard. (In OpenGL units)
 */
#define LSDefaultBillboardCentreSize 18

/**
 * @brief The texture size in pixels of a default CIW billboard texture.
 */
#define LSDefaultBillboardTextureSize 64

/**
 * @brief The field of view for the current viewport.
 */
#define LSFOV 60.0f//50.1f

/**
 * @brief The minimum refresh time
 */
#define LSMinimumRefreshTime 10

/**
 * @brief The minimum refresh distance
 */
#define LSMinimumRefreshDistance 3

/**
 * @brief The amount of vertices used to construct a billboard.
 */
#define LSBillboardVertices 4

/**
 * @brief The amount of indices used to construct a billboard.
 */
#define LSBillboardIndices 6

/**
 * @brief Default JPEG quality used for all image uploads to server
 */
#define kDefaultJPEGQuality 0.85f

//#define LSFocusedPoiUpdated				@"LSFocusedPoiUpdated"
//#define LSOldFocusedPoi					@"LSOldFocusedPoi"
//#define LSNewFocusedPoi					@"LSNewFocusedPoi"
//#define LSSelectedPoiUpdated			@"LSSelectedPoiUpdated"
//#define LSOldSelectedPoi				@"LSOldSelectedPoi"
//#define LSNewSelectedPoi				@"LSNewSelectedPoi"

// Values for server requests
#define LSGetBackToAppUrl				@"//dev.layar.com/media/getbacktoapp.html"
#define LSAboutLayarPageUrl             @"http://www.layar.com/resources/documents/aboutlayar/"

// Endpoint environment
// Possible values are:
//#define ENDPOINT_ENVIRONMENT_STAGING
//#define ENDPOINT_ENVIRONMENT_PREPRODUCTION
#define ENDPOINT_ENVIRONMENT_PRODUCTION
//#define ENDPOINT_ENVIRONMENT_TEST
//#define ENDPOINT_ENVIRONMENT_LEELOO

#if defined(ENDPOINT_ENVIRONMENT_STAGING)

// Staging environment 
#define LSServerBaseUrl					@"http://staging-79-125-15-35.layar.com/api/layer"				
#define LSUserBaseUrl					@"https://staging-79-125-15-35.layar.com/api/user"
#define LSPaymentsBaseUrl				@"http://staging-79-125-15-35.layar.com/api/payments"
#define LSStreamBaseUrl					@"http://staging-79-125-15-35.layar.com/api/stream"
#define LSBaseCategoryIconUrl			@"http://staging-79-125-15-35.layar.com/static/category_icons"
#define LSBaseImageUrl					@"http://staging-79-125-15-35.layar.com/images"
#define LSCategoryBaseUrl				@"http://staging-79-125-15-35.layar.com/api/category/all"
#define LSCategoryCountBaseUrl			@"http://staging-79-125-15-35.layar.com/api/category/count"
#define LSFeedbackBaseUrl				@"http://staging-79-125-15-35.layar.com/api/stream/events"
#define LSSocialBaseUrl					@"http://staging-79-125-15-35.layar.com/social"
#define LSUserInfoBaseUrl				@"http://staging-79-125-15-35.layar.com/api/user"
#define LSSocialShareBaseUrl			@"http://staging-79-125-15-35.layar.com/api/social/share"
#define LSAnalyticsUrl					@"http://test-79-125-2-194.layar.com/stats/log/"
#define LSServerEnvironmentString       @"staging"

#elif defined(ENDPOINT_ENVIRONMENT_TEST)

// Test environment
#define LSServerBaseUrl					@"http://test-79-125-2-194.layar.com/api/layer"
#define LSUserBaseUrl					@"https://test-79-125-2-194.layar.com/api/user"
#define LSPaymentsBaseUrl				@"http://test-79-125-2-194.layar.com/api/payments"
#define LSStreamBaseUrl					@"http://test-79-125-2-194.layar.com/api/stream"
#define LSBaseCategoryIconUrl			@"http://test-79-125-2-194.layar.com/static/category_icons"
#define LSCategoryBaseUrl				@"http://test-79-125-2-194.layar.com/api/category/all"
#define LSBaseImageUrl					@"http://test-79-125-2-194.layar.com/images"
#define LSCategoryCountBaseUrl			@"http://test-79-125-2-194.layar.com/api/category/count"
#define LSFeedbackBaseUrl				@"http://test-79-125-2-194.layar.com/api/stream/events"
#define LSSocialBaseUrl					@"http://test-79-125-2-194.layar.com/social"
#define LSUserInfoBaseUrl				@"http://test-79-125-2-194.layar.com/api/user"
#define LSSocialShareBaseUrl			@"http://test-79-125-2-194.layar.com/api/social/share"
#define LSAnalyticsUrl					@"http://test-79-125-2-194.layar.com/stats/log/"
#define LSServerEnvironmentString       @"test"

#elif defined(ENDPOINT_ENVIRONMENT_PREPRODUCTION)

// Pre-production environment
#define LSServerBaseUrl					@"http://pre-prod.layar.com/api/layer"
#define LSUserBaseUrl					@"https://pre-prod.layar.com/api/user"
#define LSPaymentsBaseUrl				@"http://pre-prod.layar.com/api/payments"
#define LSStreamBaseUrl					@"http://pre-prod.layar.com/api/stream"
#define LSBaseCategoryIconUrl			@"http://pre-prod.layar.com/static/category_icons"
#define LSCategoryBaseUrl				@"http://pre-prod.layar.com/api/category/all"
#define LSBaseImageUrl					@"http://pre-prod.layar.com/images"
#define LSCategoryCountBaseUrl			@"http://pre-prod.layar.com/api/category/count"
#define LSFeedbackBaseUrl				@"http://pre-prod.layar.com/api/stream/events"
#define LSSocialBaseUrl					@"http://pre-prod.layar.com/social"
#define LSUserInfoBaseUrl				@"http://pre-prod.layar.com/api/user"
#define LSSocialShareBaseUrl			@"http://pre-prod.layar.com/api/social/share"
#define LSAnalyticsUrl					@"http://pre-prod.layar.com/stats/log/"
#define LSServerEnvironmentString       @"preprod"

#elif defined(ENDPOINT_ENVIRONMENT_LEELOO)

// Leeloo test environment
#define LSServerBaseUrl					@"http://leeloo-test.layar.com/api/layer"
#define LSUserBaseUrl					@"https://leeloo-test.layar.com/api/user"
#define LSPaymentsBaseUrl				@"http://leeloo-test.layar.com/api/payments"
#define LSStreamBaseUrl					@"http://leeloo-test.layar.com/api/stream"
#define LSBaseCategoryIconUrl			@"http://leeloo-test.layar.com/static/category_icons"
#define LSBaseImageUrl					@"http://leeloo-test.layar.com/images"
#define LSCategoryBaseUrl				@"http://leeloo-test.layar.com/api/category/all"
#define LSCategoryCountBaseUrl			@"http://leeloo-test.layar.com/api/category"
#define LSFeedbackBaseUrl				@"http://leeloo-test.layar.com/api/stream/events"
#define LSSocialBaseUrl					@"http://leeloo-test.layar.com/social"
#define LSUserInfoBaseUrl				@"http://leeloo-test.layar.com/api/user"
#define LSSocialShareBaseUrl			@"http://leeloo-test.layar.com/api/social/share"
#define LSAnalyticsUrl					@"http://test-79-125-2-194.layar.com/stats/log/"
#define LSServerEnvironmentString       @"leeloo"

#elif defined(ENDPOINT_ENVIRONMENT_PRODUCTION)

// Production environment
#define LSServerBaseUrl					@"http://dev.layar.com/api/layer"
#define LSUserBaseUrl					@"https://dev.layar.com/api/user"
#define LSPaymentsBaseUrl				@"http://dev.layar.com/api/payments"
#define LSStreamBaseUrl					@"http://dev.layar.com/api/stream"
#define LSBaseCategoryIconUrl			@"http://dev.layar.com/static/category_icons"
#define LSBaseImageUrl					@"http://dev.layar.com/images"
#define LSCategoryBaseUrl				@"http://dev.layar.com/api/category/all"
#define LSCategoryCountBaseUrl			@"http://dev.layar.com/api/category"
#define LSFeedbackBaseUrl				@"http://dev.layar.com/api/stream/events"
#define LSSocialBaseUrl					@"http://dev.layar.com/social"
#define LSUserInfoBaseUrl				@"http://dev.layar.com/api/user"
#define LSSocialShareBaseUrl			@"http://dev.layar.com/api/social/share"
#define LSServerEnvironmentString       @""

// Endpoint for analytics. For external player always point to production
#if defined (DISTRIBUTION) || !defined (LPINTERNALBUILD)
#define LSAnalyticsUrl					@"http://stats-ec2-46-137-101-227.layar.com/stats/log/" 
#else
#define LSAnalyticsUrl					@"http://test-79-125-2-194.layar.com/stats/log/"
#endif

#endif

//Social logging in/connecting tags
#define LSFacebookTag					@"facebook"
#define LSTwitterTag					@"twitter"
#define LSDeveloperTag					@"developer"

#define LSSuccessTag					@"success"
#define LSFailTag						@"fail"

//Request parameter keys

//Common parameters
#define LSResponseCodeParameterKey		@"responseCode"
#define LSResponseMessageParameterKey	@"responseMessage"
#define LSPhoneIdParameterKey			@"phoneId"
#define LSCountryCodeParameterKey		@"countryCode"
#define LSLocalCountryCodeParameterKey	@"localCountryCode"
#define LSCategoriesParameterKey		@"categories"
#define LSCurrencyParameterKey			@"currency"

//Authentication parameters
#define LSKeepNotifiedParameterKey		@"keep_notified"

//Authentication POI parameters
#define LSUsernameParameterKey			@"username"
#define LSPasswordParameterKey			@"password"
#define LSEmailParameterKey				@"email"
#define LSTokenParameterKey				@"token"
#define LSAccessTokenParameterKey		@"access_token"

//Layer parameters
#define LSLayerParameterKey				@"layer"
#define LSLayerNameParameterKey			@"name"
#define LSLayerIconParameterKey			@"icon"
#define LSModifiedParameterKey			@"modified"
#define LSPublisherParameterKey			@"publisher"
#define LSPublisherEmailParameterKey	@"publisher_email"
#define LSShortDescriptionParameterKey	@"shortDescription"
#define LSLayerStatusParameterKey		@"status"
#define LSLayerTitleParameterKey		@"title"
#define LSLayerLinkUrlParameterKey		@"linkUrl"
#define LSLayerTypeParameterKey			@"type"
#define LSLayerPremiumParameterKey		@"premium"
#define LSLayerPriceParameterKey		@"price"
#define LSLayerPurchasedParameterKey	@"purchased"

//Layer and POI parameters
#define LSGeolocationParameterKey       @"geolocation"
#define LSReferenceImageParameterKey    @"referenceImage"
#define LSReferenceImageThumbnailUrlKey @"thumbnailUrl"
#define LSReferenceImageFeaturesUrlKey  @"featuresUrl"
#define LSReferenceImageKeyKey          @"key"
#define LSReferenceImageIdKey           @"id"
#define LSLatitudeUrlParameterKey       @"lat"
#define LSLongitudeUrlParameterKey      @"lon"
#define LSLanguageParameterKey          @"lang"
#define LSAltitudeParameterKey          @"alt"
#define LSRelativeAltitudeParameterKey  @"relativeAlt"
#define LSRadiusParameterKey            @"radius"
#define LSPageParameterKey              @"pageKey"
#define LSShowPricedContentParameterKey @"showPriced"
#define LSAllCategoriesKeyParameterKey  @"all"
#define LSSearchTermsParameterKey       @"searchTerms"

//Response parameter keys
#define LSLayersParameterKey			@"layers"
#define LSMorePagesParameterKey			@"morePages"
#define LSNextPageParameterKey			@"nextPageKey"

//Sharing keys
#define LSServicesKey					@"services"
#define LSMessageKey					@"message"
#define LSLocationNameKey				@"location_name"
#define LSScreenshotKey					@"screenshot"
#define LSLinkKey						@"link"
#define LSTitleKey						@"title"
#define LSDescriptionKey				@"description"
#define LSIconURLKey					@"iconURL"
#define LSIconKey						@"icon"
#define LSDefaultTextKey				@"defaultText"
#define LSShareTypeKey					@"share_type"
#define LSShareTypeActionKey			@"action"
#define LSShareTypeLayerKey				@"layer"
#define LSShareTypeScreenshot			@"screenshot"

#define LSLayarSupportSite				@"support@layar.com"

#define LPExtendedBIWActionFired        @"LPExtendedBIWActionFired"

#pragma mark -
#pragma mark Enums

#if defined(__cplusplus)

extern "C"{
	
#endif

/**
 * @brief The orientation of the overlay view
 */
typedef enum LSOverlayOrientation
{
	LSOverlayOrientationUp = 0, /**< The orientation of the device when held in a vertical orientation with the screen parallel to the gravity vector */
	LSOverlayOrientationDown, /**< The orientation of the device when in an inverted vertical orientation with the screen parallel to the gravity vector */
	LSOverlayOrientationLeft, /**< The orientation of the device when held in a horizontal position with the screen perpendicular to the gravity vector and the top of the device orientated to the users left */
	LSOverlayOrientationRight /**< The orientation of the device when held in a horizontal position with the screen perpendicular to the gravity vector and the top of the device orientated to the users right */
} LSOverlayOrientation;

/**
 * @brief 3D vector
 */
typedef struct LSVector3
{
    float x; /**< The x-component of the vector */
    float y; /**< The y-component of the vector */
    float z; /**< The z-component of the vector */
} LSVector3;    
    
/**
 * @brief The rotation values of a POI.
 */
typedef struct LSRotate
{
	BOOL rel;/**< YES if the transformation is relative to the user, NO if it is absolute in terms of the world coordinates */
    float angle;/**< The angle of the rotation of the POI about it's y-axis in degrees */
    LSVector3 axis;/**< The axis of the rotation */
} LSRotate;
    
/**
 * @brief The geographical location of the device expressed as latitude and longitude
 */
typedef struct LSGeolocation
{
	float lat;/**< Longitude */
	float lon;/**< Latitude */
	int alt;/**< Altitude */
} LSGeolocation;

/**
 * @brief The transformation values of a POI.
 */
typedef struct LSTransform
{
	float scale;/**< The scale of the transformation that must be applied to the POIs size */
    LSRotate rotate;/**< The rotation of the POI */
	LSVector3 translate;/**< The translation of the POI */
} LSTransform;

/**
 * @brief The BIW style
 */	
typedef enum LSBIWStyle 
{
	LSBIW_STYLE_DEFAULT, /**< Default BIW style */
	LSBIW_STYLE_CLASSIC, /**< Classic BIW style */
	LSBIW_STYLE_COLLAPSED/**< Collapsed BIW style */
}
LSBIWStyle;

/**
 * @brief A 2D bounding box
 */
typedef struct LSBox
{
	float x;  /**< The x-coordinate of the box's origin */
	float y; /**< The y-coordinate of the box's origin */
	float width; /**< The width (and height) of the box */
} LSBox;

/**
 * @brief A 2D vector used for texture coordinates
 */
typedef struct LSVector2
{
	float u; /**< The u component of the vector */
	float v; /**< The v component of the vector */
} LSVector2;

/**
 * @brief 4D vector
 */
typedef struct LSVector4
{
	float x; /**< The x-component of the vector */ 
	float y; /**< The y-component of the vector */
	float z; /**< The z-component of the vector */
	float w; /**< The w-component of the vector */
} LSVector4;

typedef struct LSMatrix4
{
	GLfloat m[4][4];
} LSMatrix4;

/**
 * @brief A RGBA representation of a color
 */
typedef struct LSColor
{
	float r; /**< The red component of color */
	float g; /**< The green component of color */
	float b; /**< The blue component of color */
	float a; /**< The alpha component of color */
} LSColor;

/**
 * @brief The orientation of the device
 */
typedef struct LSOrientation
{
	double heading; /**< The heading heading of the device */
	LSVector3 forwardVector; /**< The 3D vector representing the direction in which the user is viewing the device. */
	LSVector3 upVector; /**< The 3D vector representing the top of the device. It should run parallel to the device's screen */
} LSOrientation;

/**
 * @brief Geographical information pertaining to the difference between two geographical locations
 */
typedef struct LSBearingInfo
{
	double distance; /**< The distance between the two coordinates */
	double initialBearing; /**<  */
	double finalBearing; /**<  */
} LSBearingInfo;

/**
 * @brief Geographical information pertaining to the difference between two geographical locations
 */   
typedef enum LSAnchorType
{
    AT_POI = 0,
    AT_FEATURE
} LSAnchorType;
/**
 * @brief The level of detail
 */
typedef enum LSLOD
{
	LOD_FULL = 0, /**< The object should be rendered using the full renderable */
	LOD_REDUCED, /**< The object should be rendered using the reduced renderable */
	LOD_ICON /**< The object should be rendered using the icon renderable */
} LSLOD;

/**
 * @brief The status of a POI
 */
typedef enum LSPOIStatus
{
	POI_STATUS_DEFAULT = 0, /**< The POI has a default status */
	POI_STATUS_FOCUSED, /**< The POI is focused */
	POI_STATUS_SELECTED /**< The POI is selected */
} LSPOIStatus;

/**
 * @brief The type of a resource
 */
typedef enum LSResourceType
{
	RESOURCE_INVALID = -1,
	RESOURCE_1D = 0,/**< The resource contains the default POI data for a layer */
	RESOURCE_2D, /**< The resource contains image data */
	RESOURCE_3D, /**< The resource contains model data in the form of vertice and texture coordinates */
	RESOURCE_VIDEO /**< The resource contains video data */
	
} LSResourceType;

/**
 * @brief The layer type
 */
typedef enum LSLayerType
{
	LAYER_TYPE_GENERIC = 1, /**< The layer contains no 3D models */
	LAYER_TYPE_3D = 2 /**< The layer contains 3D models as well as other POI types */
} LSLayerType;

/**
 * @brief The layer status
 */
typedef enum LSLayerStatus
{
	LAYER_STATUS_PUBLISHED = 1, /**< Published */
	LAYER_STATUS_FROZEN = 2, /**< Frozen */
	LAYER_STATUS_DELETED = 3, /**< Deleted */
	LAYER_STATUS_IN_DEVELOPMENT = 4, /**< In development */
	LAYER_STATUS_PENDING = 5, /**< Pending review */
	LAYER_STATUS_APPROVED = 6, /**< Approved for publication */
	LAYER_STATUS_UNPUBLISHED = 7 /**< Unpublished */
} LSLayerStatus;
    
#if defined(__cplusplus)
	
}

#endif
