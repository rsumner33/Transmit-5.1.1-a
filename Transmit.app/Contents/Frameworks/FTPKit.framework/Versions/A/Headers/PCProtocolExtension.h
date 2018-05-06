//
//  PCProtocolExtension.h
//  FTPKit
//
//  Created by Patrick B. Gibson on 2/23/15.
//  Copyright (c) 2015 Panic Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


@class FilePermissions, PCNode, PCProtocolExtensionItem;


/**
 *  Defines the extension data type and how it should be presented in the app-side UI.
 *  Note: Condensed means labels next to controls
 */
typedef NS_ENUM(NSUInteger, PCProtocolExtensionType) {
    PCProtocolExtensionTypeString,
	PCProtocolExtensionTypeStringCondensed,
	PCProtocolExtensionTypeNumber,
    PCProtocolExtensionTypeBool,
    PCProtocolExtensionTypeEnum,
	PCProtocolExtensionTypeEnumCondensed,
	PCProtocolExtensionTypeOctalMatrix,
    PCProtocolExtenstionTypeURL,
    PCProtocolExtensionTypeNil				// No user visible representation
};

/**
 *  Defines the keyboard to show for String extensions
 */
typedef NS_ENUM(NSUInteger, PCProtocolKeyboardType) {
    PCProtocolKeyboardTypeName,
    PCProtocolKeyboardTypeURL,
    PCProtocolKeyboardTypeUndefined
};

/**
 *  Validation on the item or recursively
 */
typedef NS_ENUM(NSUInteger, PCProtocolValidationState) {
	PCProtocolValidationDefault,
	PCProtocolValidationRecursive
};

/**
 *  Bitmask used with applicableNodeTypes to define where this extension should be shown
 */
typedef NS_ENUM(NSUInteger, PCProtocolNodeType) {
    PCProtocolNodeTypeFile = 1 << 0,
    PCProtocolNodeTypeFolder = 1 << 1,
    PCProtocolNodeTypeContainer = 1 << 2,
    PCProtocolNodeTypeAlias = 1 << 3,
	PCProtocolNodeTypeRoot = 1 << 4,
	PCProtocolNodeTypeAll = (PCProtocolNodeTypeFile | PCProtocolNodeTypeFolder | PCProtocolNodeTypeContainer | PCProtocolNodeTypeAlias)
};

typedef BOOL (^PCProtocolExtentsionValidationBlock)(NSArray *protocolItems, PCProtocolValidationState state);

@interface PCProtocolExtension : NSObject

- (instancetype)initWithAttributeName:(NSString *)attributeName
                           prettyName:(NSString *)prettyName
                        extensionType:(PCProtocolExtensionType)extensionType
                  enumValuesAndTitles:(NSDictionary *)enumValuesAndTitles // can be nil – if so, validateMethod is required.
                      explanatoryText:(NSString *)explanation
                       validateMethod:(PCProtocolExtentsionValidationBlock)validationBlock; // can be nil - if so, extensionType must be Enum and enumValuesAndTitles must be specified.

@property (nonatomic, readonly) NSString *attributeName;
@property (nonatomic, readonly) NSString *prettyName;
@property (nonatomic, readonly) PCProtocolExtensionType extensionType;
@property (nonatomic, readonly) NSString *explanatoryText;
@property (nonatomic, assign)   PCProtocolNodeType applicableNodeTypes;

@property (nonatomic, assign, getter=isReadonly) BOOL readonly;
@property (nonatomic, assign, getter=isCopyable) BOOL copyable;

@property (assign) BOOL supportsMultipleItems;

/**
 * If non-nil, this can be used to provide a hint to the consumer about the expected class of the attribute
 */
@property (nonatomic, assign) Class valueClass;

/**
 *  If non-nil, this transformer should be applied to the value of the attribute value
 *  then displayed to the user.
 */
@property (atomic, retain) NSValueTransformer *transformer;

/**
 *  If non-nil, this predicate block will be invoked to determine if extension items are valid to be enabled for the item.
 */
@property (nonatomic, copy) BOOL (^enablingPredicateForItems)(NSArray <PCProtocolExtensionItem *> *items);

/**
 *  Applies only to PCProtocolExtensionTypeEnum
 */
@property (nonatomic, readonly) NSDictionary *enumValuesAndTitles;

/**
 *  Applies only to PCProtocolExtensionTypeString. PCProtocolExtensionTypeNumber automatically gets a number keyboard.
 */
@property (nonatomic, assign) PCProtocolKeyboardType keyboardType;

/**
 *  Creates a parent-child relationship between reciever and extensions.
 *
 *  @param extension    The child extension.
 *  @param enabledValue The value of the parent (reciever) for which this extension will be active.
 * 
 *  @discussion
 *  If enabledValue is an NSPredicate, it will be evaluated against the parent extension's value.
 *  Otherwise, the value will be compared using isEquals:
 */
- (void)addChildExtension:(PCProtocolExtension *)extension forEnabledValue:(id)enabledValue;

/**
 *  Gets the list of child extensions
 *
 *  @return An array of all child extensions regardless of state
 *
 */
- (NSArray *)childExtensions;

/**
 *  Gets the enabled state of a child extension given some value.
 *
 *  @param extension	The child extension.
 *  @param value		Any value to test for. Typically this would be the value the parent extension is going to or has just changed to.
 *
 *  @return An enabled bool.
 */

- (BOOL)childExtension:(PCProtocolExtension*)extension isEnabledForValue:(id)value;

/**
 *  Gets the enabled extensions given some value.
 *
 *  @param value Any value to test for. Typically this would be the value the parent extension is going to or has just changed to.
 *
 *  @return An array of all child extensions active for that value.
 */
- (NSArray *)enabledChildExtensionsForValue:(id)value;

/**
 *  Tests wether or not the given value is valid for this extension.
 *
 *  @param protocolItems Any value to test.
 *  @param state on item or recursive validation
 *
 *  @return Wether or not the value is valid for this extension.
 */
- (BOOL)validates:(NSArray*)protocolItems state:(PCProtocolValidationState)state error:(NSError**)outError;

/**
 *  Sets the appropriates values on the given node for this extension.
 *
 *  @param node       The node to modify.
 *  @param attributes The attributes dictionary that (hopefully) contains the key/value for this particular attribute.
 */
- (void)updateNode:(PCNode *)node withAttributes:(NSDictionary *)attributes;

@end


@interface PCProtocolExtensionItem : NSObject

- (instancetype)initWithNode:(PCNode *)node;

@property (strong) NSDictionary <NSString *, id> *properties;
@property (copy) FilePermissions *permissions;
@property PCProtocolNodeType type;

@end

