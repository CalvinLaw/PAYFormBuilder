//
//  PAYFormBuilder.h
//  paij
//
//  Created by Simon Seyer on 01.11.13.
//  Copyright (c) 2013 redpixtec. GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef enum {
    PAYFormTableLabelStyleSimple,
    PAYFormTableLabelStyleDescription,
    PAYFormTableLabelStyleDescriptionWide,
    PAYFormTableLabelStyleEmpty,
    PAYFormTableLabelStyleNone
} PAYFormTableLabelStyle;

typedef enum {
    PAYFormButtonStyleCentered,
    PAYFormButtonStylePrimaryCentered,
    PAYFormButtonStyleHilightedCentered,
    PAYFormButtonStyleDisabledCentered,
    PAYFormButtonStyleDisclosure,
    PAYFormButtonStyleIconDisclosure,
    PAYFormButtonStyleSelection,
    PAYFormButtonStyleIconSelection,
    PAYFormButtonStyleEmpty
} PAYFormButtonStyle;


@class PAYFormTable;
@class PAYFormSection;
@class PAYFormField;
@class PAYFormSingleLineTextField;
@class PAYFormMultiLineTextField;
@class PAYFormButton;
@class PAYFormButtonGroup;
@class PAYFormHeader;
@class PAYFormView;
@protocol PAYTableBuilder;
@protocol PAYSectionBuilder;
@protocol PAYButtonGroupBuilder;
@protocol PAYFormCell;


typedef void(^PAYFormTableCompletionBlock)();
typedef void(^PAYFormSectionCompletionBlock)();
typedef void(^PAYFormFieldCompletionBlock)();
typedef void(^PAYFormSelectionBlock)(PAYFormView *);
typedef id(^PAYFormFieldFormatBlock)(PAYFormField *, id);
typedef id(^PAYFormFieldCleanBlock)(PAYFormField *, id);
typedef void(^PAYFormFieldErrorStylingBlock)(id, NSError *);
typedef void (^PAYFormTableSuccessBlock)();
typedef BOOL (^PAYFormTableFailBlock)(NSError *error);
typedef NSError *(^PAYFormFieldValidationBlock)(PAYFormField *);
typedef NSError *(^PAYFormValidationBlock)();

extern NSString * const PAYFormBuilderErrorControlKey;
extern NSString * const PAYFormBuilderErrorRecoveryOptionsKey;
extern NSString * const PAYFormBuilderErrorDomain;
extern NSInteger const PAYFormBuilderErrorCode;

@protocol PAYTableBuilder <NSObject>

/*
 Calls done when last text field is finished by the user. Has to be called inside the buildTable block.
 */
@optional
@property (nonatomic, assign) BOOL selectFirstField;
@property (nonatomic, assign) BOOL finishOnLastField;

@property (nonatomic, copy) PAYFormValidationBlock validationBlock;
@property (nonatomic, copy) PAYFormTableCompletionBlock completionBlock;
@property (nonatomic, copy) PAYFormTableSuccessBlock formSuccessBlock;
@property (nonatomic, copy) PAYFormTableFailBlock formFailBlock;

@required
- (PAYFormSection *)addSectionWithContentBlock:(void(^)(id<PAYSectionBuilder>))contentBlock;
- (PAYFormSection *)addSectionWithContentBlock:(void(^)(id<PAYSectionBuilder>))contentBlock labelStyle:(PAYFormTableLabelStyle)style;
- (PAYFormSection *)addSectionWithHeaderBlock:(void(^)(PAYFormHeader *))headerBlock contentBlock:(void(^)(id<PAYSectionBuilder>))contentBlock;
- (PAYFormSection *)addSectionWithName:(NSString *)name labelStyle:(PAYFormTableLabelStyle)style contentBlock:(void(^)(id<PAYSectionBuilder>))contentBlock;
- (PAYFormSection *)addSectionWithName:(NSString *)name labelStyle:(PAYFormTableLabelStyle)style headerBlock:(void(^)(PAYFormHeader *))headerBlock contentBlock:(void(^)(id<PAYSectionBuilder>))contentBlock;

@end


@protocol PAYSectionBuilder <NSObject>

- (PAYFormSingleLineTextField *)addFieldWithPlaceholder:(NSString *)placeholder;
- (PAYFormSingleLineTextField *)addFieldWithPlaceholder:(NSString *)placeholder configureBlock:(void(^)(PAYFormSingleLineTextField *))configureBlock;
- (PAYFormSingleLineTextField *)addFieldWithName:(NSString *)name placeholder:(NSString *)placeholder;
- (PAYFormSingleLineTextField *)addFieldWithName:(NSString *)name placeholder:(NSString *)placeholder configureBlock:(void(^)(PAYFormSingleLineTextField *))configureBlock;

- (PAYFormMultiLineTextField *)addTextViewWithPlaceholder:(NSString *)placeholder;
- (PAYFormMultiLineTextField *)addTextViewWithPlaceholder:(NSString *)placeholder configureBlock:(void(^)(PAYFormMultiLineTextField *))configureBlock;

- (PAYFormButton *)addButtonWithText:(NSString *)text style:(PAYFormButtonStyle)style selectionBlock:(PAYFormSelectionBlock)selectionBlock;
- (PAYFormButton *)addButtonWithText:(NSString *)text style:(PAYFormButtonStyle)style selectionBlock:(PAYFormSelectionBlock)selectionBlock configureBlock:(void(^)(PAYFormButton *))configureBlock;

- (PAYFormButtonGroup *)addButtonGroupWithMutliSelection:(BOOL)multiSelection contentBlock:(void(^)(id<PAYButtonGroupBuilder>))contentBlock;

- (void)addView:(void(^)(PAYFormView *))configureBlock;

@end

@protocol PAYButtonGroupBuilder <NSObject>

@optional
- (void)select:(id)value;

@required
- (PAYFormButton *)addOption:(id)value withText:(NSString *)text;
- (PAYFormButton *)addOption:(id)value withText:(NSString *)text icon:(UIImage *)icon;
- (PAYFormButton *)addOption:(id)value withText:(NSString *)text icon:(UIImage *)icon selectionBlock:(PAYFormSelectionBlock)selectionBlock;

@end


@protocol PAYFormRow <NSObject>

- (UITableViewCell *)cell;
- (PAYFormSection *)section;

@optional
- (void)didSelectRow;

@end


@protocol PAYValidatableFormCell <NSObject>


- (NSError *)validate;

@end
