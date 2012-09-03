//
//  Spriter_Cocos2d_XAppController.h
//  Spriter-Cocos2d-X
//
//  Created by Young Peter on 9/4/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

