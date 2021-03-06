//
//  SimpleEnum.h
//

/*!
 @brief Helper macro to create an enum and associated C functions. The macro does a few things:
        • defines the enum with the supplied values
        • adds a final parameter with the format ENUM_NAMECount (helpful when iterating through the enum).
        • creates a string -> enum C function with the format ENUM_NAMEForString(NSString* enumString)
        • created an enum -> string C function with the format StringForENUM_NAME(ENUM_NAME enumValue)
 */
#define SimpleEnumWithValues(EnumName, ...) SimpleEnumStartingAtIntWithValues(EnumName, 0, __VA_ARGS__)


/*!
 @brief Helper macro to create an enum with it's first value set and associated C functions. The macro does a few things:
        • defines the ENUM_NAME with the supplied values
        • sets the first value to startIndex
        • adds a final parameter with the format ENUM_NAMECount (helpful when iterating through the enum).
        • creates a string -> enum C function with the format StringForENUM_NAME(ENUM_NAME enumValue)
        • created an enum -> string C function with the format ENUM_NAMEForString(NSString* enumString)
 */
#define SimpleEnumStartingAtIntWithValues(EnumName, startIndex, firstEnumValue, ...) \
    /* define enum type, assign it's values and add a count value at the end */\
    typedef NS_ENUM(NSInteger, EnumName) {firstEnumValue = startIndex, ##__VA_ARGS__, EnumName##Count}; \
\
    /* define enum to string function */\
    NS_INLINE NSString* StringFor##EnumName(EnumName enumValue) {\
        static NSArray *enumStrings;\
        static dispatch_once_t onceToken;\
        dispatch_once(&onceToken, ^{\
            const char *args = #firstEnumValue ", " #__VA_ARGS__;\
            enumStrings = [@(args) componentsSeparatedByString:@", "];\
        });\
        return enumStrings[enumValue];\
    }\
\
    /* define string to enum function*/\
    NS_INLINE EnumName EnumName##ForString(NSString* enumString) {\
        static NSArray *enumStrings;\
        static dispatch_once_t onceToken;\
        dispatch_once(&onceToken, ^{\
            const char *args = #firstEnumValue ", " #__VA_ARGS__;\
            enumStrings = [@(args) componentsSeparatedByString:@", "];\
        });\
        return [enumStrings indexOfObject:enumString];\
    }
