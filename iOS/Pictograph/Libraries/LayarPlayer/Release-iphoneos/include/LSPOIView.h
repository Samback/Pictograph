/**
 * @file LSPOIView.h
 * @brief This file contains the LSPOIView class.
 * @author Lawrence Lee, Layar B.V.
 * @date 23rd August 2010
 */

//System imports
#import <Foundation/Foundation.h>

@class LSPOI;
@class LSPOIModel;

/**
 * @brief A view that recieves notifications from a LSPOIModel implementation
 */
@protocol LSPOIView <NSObject>

/**
 * @brief Called when a model will insert POI's
 *
 * @param model The model that will insert the POI's
 * @param indexes The indexes at which the POI's will be inserted
 */
- (void)model:(LSPOIModel*)model willInsertPOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when a model inserted POI's
 *
 * @param model The model that inserted the POI's
 * @param indexes The indexes of the POI's that were inserted
 */
- (void)model:(LSPOIModel*)model didInsertPOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when a model will remove POI's
 *
 * @param model The model that will remove the POI's
 * @param indexes The indexes from which the POI's will be removed
 */
- (void)model:(LSPOIModel*)model willRemovePOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when a model removed POI's
 *
 * @param model The model that removed the POI's
 * @param indexes The indexes from which the POI's were removed
 */
- (void)model:(LSPOIModel*)model didRemovePOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when a model will replace POI's
 *
 * @param model The model that will replace the POI's
 * @param indexes The indexes at which the POI's will be replaced
 */
- (void)model:(LSPOIModel*)model willReplacePOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when a model replace POI's
 *
 * @param model The model that replace the POI's
 * @param indexes The indexes at which the POI's were replaced
 */
- (void)model:(LSPOIModel*)model didReplacePOIsAtIndexes:(NSArray*)indexes;

/**
 * @brief Called when model updates the selected POI
 *
 */
- (void)model:(LSPOIModel*)model updatedSelectedPOIFrom:(LSPOI*)fromPOI toPOI:(LSPOI*)toPOI;
@end
