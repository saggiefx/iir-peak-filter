
set (BaseTargetName ${PROJECT_NAME})
project(${BaseTargetName} LANGUAGES CXX VERSION 0.0.1)

juce_add_plugin("${BaseTargetName}"
        COMPANY_NAME "saggiefx"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT FALSE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD FALSE
        PLUGIN_MANUFACTURER_CODE Juce
        PLUGIN_CODE Dem0
        FORMATS VST3 AU Standalone
        PRODUCT_NAME "PeakFilter")

juce_generate_juce_header(${BaseTargetName})


set(KNOB_RANGE_START 0)
set(KNOB_RANGE_END 99)
set(KNOB_FILES_LIST "")

foreach(KNOB_NUM RANGE ${KNOB_RANGE_START} ${KNOB_RANGE_END})
    string(LENGTH "${KNOB_NUM}" KNOB_NUM_LENGTH)
    math(EXPR NUM_ZEROS_COUNT "5 - ${KNOB_NUM_LENGTH}")
    if (NUM_ZEROS_COUNT LESS 0)
        set(NUM_ZEROS_COUNT 0)
    endif()
    string(REPEAT "0" ${NUM_ZEROS_COUNT} KNOB_NUM_PADDED)
    set(KNOB_NUM_Padded "${KNOB_NUM_PADDED}${KNOB_NUM}")

    set(KNOB_NAME "volume_${KNOB_NUM_Padded}")

    list(APPEND KNOB_FILES_LIST "Assets/Knob/${KNOB_NAME}.png") 
endforeach()

juce_add_binary_data(Binary SOURCES
        Assets/radio_front.png
        ${KNOB_FILES_LIST}
        ) 

file(GLOB_RECURSE SOURCE_FILES "Source/*.cpp")

target_sources(${BaseTargetName} PRIVATE ${SOURCE_FILES})

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

target_link_libraries(${BaseTargetName} PUBLIC
        Binary
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
    	juce::juce_dsp
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)
