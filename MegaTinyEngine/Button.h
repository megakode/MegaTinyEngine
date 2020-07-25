//
// Created by peter on 15/07/2020.
//

#ifndef SIMPLEWESTERNGAME_BUTTON_H
#define SIMPLEWESTERNGAME_BUTTON_H

#include "MegaTinyEngine/Core.h"
#include "MegaTinyEngine/Sprite.h"

namespace Engine {



class Button : public Sprite, public std::enable_shared_from_this<Button> {

    public:

        Button(const std::string& textureIdentifier, int tag = 0 );

        void draw(SDL_Renderer *renderer) override;

        /// Set whether the button will be highlighted when drawn.
        void setHighlight(bool highlighted);

        /// Set callback to be called when button is pressed. Is triggered on mouse up.
        ///
        /// Example:
        ///
        /// button->setCallback(std::bind(&MyClass::buttonWasPressed,this,std::placeholders::_1));
        ///
        /// or as lambda function:
        ///
        /// auto lambda = [] (int tag) { std::cout << "lambda button press " << tag << std::endl; };
        ///  button->setCallback(lambda);
        ///
        /// \param callback
        void setCallback(const std::function<void(int)>& callback) {
            m_callback = callback;
        }

        bool handleEvent(const InputEvent &event) override;

    private:

        std::function<void(int)> m_callback;

        /// The tag that identifies this button. Is also sent as a parameter to the IButtonDelegate when the button is pressed.
        int m_tag;

        /// Whether the button will be highlighted when drawn.
        bool m_highlighted = false;


    };

}

#endif //SIMPLEWESTERNGAME_BUTTON_H
