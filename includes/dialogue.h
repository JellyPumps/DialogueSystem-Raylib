#pragma once

#include <string>
#include <vector>

#include "raylib.h"

enum class ContainerPosition
{
    BottomCenter,
    BottomLeft
};

struct DialogueNode
{
    std::string character;
    std::string dialogue;
    std::vector<int> nextNodeID; 
};

struct Container
{
    Rectangle contBox;
    Rectangle textBox;
    Texture2D charImage;
    Vector2 imagePosition;
};

class Dialogue
{
    public:
        Dialogue();
        ~Dialogue();

        void LoadDialogue(const std::string &filepath);
        void StartDialogue();
        void ProcessInput();
        void SetContainerPosition(ContainerPosition position);
        void SetImage(const Texture2D& imageTexture);
    
    private:
        std::vector<DialogueNode> node;
        int currentNodeID;
        bool dialogueFinished;
        std::string removedCharacters;

        Container container;

        template<typename T>
        T clamp(const T& value, const T& minValue, const T& maxValue)
        {
            return value < minValue ? minValue : (value > maxValue ? maxValue : value);
        }

        bool IsDialogueFinished() const;
        void CalculateContainerSize();
        void CreateTextbox();
        void DrawDialogueText(const int fontSize);
};