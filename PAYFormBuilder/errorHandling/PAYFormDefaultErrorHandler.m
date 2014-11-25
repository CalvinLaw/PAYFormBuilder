//
//  DefaultErrorHandler.m
//  PAYFormBuilder
//
//  Created by Simon Seyer on 11.04.14.
//  Copyright (c) 2014 Paij. All rights reserved.
//

#import "PAYFormDefaultErrorHandler.h"
#import <BlocksKit+UIKit.h>
#import <libextobjc/extobjc.h>
#import "NSError+PAYComfort.h"

#import "PAYFormView+PAYFormDefaultErrorHandlerProtected.h"
#import "PAYFormView_protected.h"
#import "PAYFormErrorMessage.h"
#import "PAYFormErrorMessage_protected.h"

#import "PAYFormErrorStyler.h"
#import "PAYFormErrorMessageManager_protected.h"

@implementation PAYFormDefaultErrorHandler

static NSString *buttonText;
+ (void)setButtonText:(NSString *)text {
    buttonText = text;
}

+ (NSString *)buttonText {
    return buttonText;
}

+ (PAYFormTableFailBlock)failBlock {
    return ^BOOL(NSArray *errors) {
        NSAssert(buttonText, @"The button text of the default error handler has to be set, when it is used to show error messages");
        
        // just handle the first error
        NSError *error = errors.firstObject;
        PAYFormErrorMessage *errorMessage = [PAYFormErrorMessageManager errorMessageForError:error];
        
        UIAlertView* alertView = [UIAlertView bk_alertViewWithTitle:[errorMessage titleForField:error.field]
                                                            message:[errorMessage messageForField:error.field]];
        [alertView bk_addButtonWithTitle:buttonText handler:^{
            if ([error.field isKindOfClass:PAYFormView.class]) {
                [(PAYFormView *)error.field becomeFirstResponder];
            }
        }];
        
        [alertView show];
        return NO;
    };
}

@end
