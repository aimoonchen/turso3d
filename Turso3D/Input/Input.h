// For conditions of distribution and use, see copyright notice in License.txt

#pragma once

#include "../Math/IntVector2.h"
#include "../Object/Object.h"

struct SDL_Window;

/// Button states for keys, mouse and controller.
enum ButtonState
{
    STATE_UP = 0,
    STATE_RELEASED,
    STATE_DOWN,
    STATE_PRESSED
};

/// Button press or release event.
class ButtonEvent : public Event
{
public:
    union
    {
        /// Key code.
        unsigned keyCode;
        /// Mouse button.
        unsigned button;
    };

    /// Repeat flag.
    bool repeat;
};

/// Text input event.
class TextInputEvent : public Event
{
public:
    /// Text in UTF8 format.
    std::string text;
};

/// Delta motion event.
class MovementEvent : public Event
{
public:
    /// Delta movement since last event.
    IntVector2 delta;
};

/// %Input collection subsystem.
class Input : public Object
{
    OBJECT(Input);

public:
    /// Construct and register subsystem. Requires an OS-level window.
    Input(SDL_Window* window);
    /// Destruct.
    ~Input();

    /// Poll OS input events from the window.
    void Update();
   
    /// Return state of a key.
    ButtonState KeyState(unsigned keyCode) const;
    /// Return state of a mouse button.
    ButtonState MouseButtonState(unsigned num) const;
    /// Return whether key was pressed this frame.
    bool KeyPressed(unsigned keyCode) const { return KeyState(keyCode) == STATE_PRESSED; }
    /// Return whether key was released this frame.
    bool KeyReleased(unsigned keyCode) const { return KeyState(keyCode) == STATE_RELEASED; }
    /// Return whether key was pressed or held down this frame.
    bool KeyDown(unsigned keyCode) const { ButtonState state = KeyState(keyCode); return state >= STATE_DOWN; }
    /// Return text input since last frame.
    const std::string& TextInput() const { return textInput; }
    /// Return whether mouse button was pressed this frame.
    bool MouseButtonPressed(unsigned button) const { return MouseButtonState(button) == STATE_PRESSED; }
    /// Return whether key was released this frame.
    bool MouseButtonReleased(unsigned button) const { return MouseButtonState(button) == STATE_RELEASED; }
    /// Return whether key was pressed or held down this frame.
    bool MouseButtonDown(unsigned button) const { ButtonState state = MouseButtonState(button); return state >= STATE_DOWN; }
    /// Return mouse movement since last frame.
    const IntVector2& MouseMove() const { return mouseMove; }
    /// Return mouse wheel scroll since last frame.
    const IntVector2& MouseWheel() const { return mouseWheel; }
    /// Return whether has input focus.
    bool HasFocus() const { return focus; }
    /// Return whether application exit was requested.
    bool ShouldExit() const { return shouldExit; }
    /// Return the OS-level window.
    SDL_Window* Window() const { return window; }
    
    /// Text input event.
    TextInputEvent textInputEvent;
    /// Key press event.
    ButtonEvent keyPressEvent;
    /// Key release event.
    ButtonEvent keyReleaseEvent;
    /// Mouse button press event.
    ButtonEvent mousePressEvent;
    /// Mouse button release event.
    ButtonEvent mouseReleaseEvent;
    /// Mouse move event.
    MovementEvent mouseMoveEvent;
    /// Mouse wheel scroll event.
    MovementEvent mouseWheelEvent;
    /// Window input focus gained event.
    Event focusGainedEvent;
    /// Window input focus lost event.
    Event focusLostEvent;
    /// Exit request event.
    Event exitRequestEvent;

private:
    /// OS-level window.
    SDL_Window* window;
    /// Accumulated mouse movement.
    IntVector2 mouseMove;
    /// Accumulated mouse wheel movement.
    IntVector2 mouseWheel;
    /// Accumulated text input.
    std::string textInput;
    /// Key states.
    std::map<unsigned, ButtonState> keyStates;
    /// Mouse button states.
    std::map<unsigned, ButtonState> mouseButtonStates;
    /// Input focus flag.
    bool focus;
    /// Exit request flag.
    bool shouldExit;
};
