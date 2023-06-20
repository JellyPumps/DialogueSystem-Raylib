#include "dialogue.h"

// Constructor
Dialogue::Dialogue()
{
    currentNodeID   = -1;
    dialogueFinished= false;

    containerPosX   = 0;
    containerPosY   = 0;
    containerSizeX  = 0;
    containerSizeY  = 0;

    containerBox = { 0, 0, 0, 0 };
}

// Deconstuctor
Dialogue::~Dialogue() {}


// Dialogue Functions
void Dialogue::LoadDialogue(const std::string &filepath) {}

void Dialogue::StartDialogue()
{
    currentNodeID = 0;
    dialogueFinished = false;
}

bool Dialogue::IsDialogueFinished() const
{
    return dialogueFinished;
}

void Dialogue::ProcessInput() {}

void Dialogue::SetContainerPosition(ContainerPosition position)
{
    // Creates X & Y padding using 6.25% of screen size
    int paddingX = static_cast<int>(GetScreenWidth() * 0.0625);
    int paddingY = static_cast<int>(GetScreenHeight() * 0.0625);

    switch (position)
    {
        case ContainerPosition::BottomCenter:
            containerPosX = GetScreenWidth() / 2 - containerSizeX / 2;
            containerPosY = GetScreenHeight() - containerSizeY;
            break;
        case ContainerPosition::BottomLeft:
            containerPosX = 0;
            containerPosY = GetScreenHeight() - containerSizeY;
            break;
    }

    // Clamp the container position within the screen bounds
    containerPosX = clamp(containerPosX, 0, GetScreenWidth() - containerSizeX);
    containerPosY = clamp(containerPosY, 0, GetScreenHeight() - containerSizeY);
}