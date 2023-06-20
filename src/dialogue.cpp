#include "dialogue.h"

// Constructor
Dialogue::Dialogue()
{
    currentNodeID   = -1;
    dialogueFinished= false;
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
            container.contBox.x = GetScreenWidth() / 2.0 - container.contBox.width / 2.0;
            container.contBox.y = GetScreenHeight() - container.contBox.height;
            break;
        case ContainerPosition::BottomLeft:
            container.contBox.x = 0;
            container.contBox.y = GetScreenHeight() - container.contBox.height;
            break;
    }

    // Clamp the container position within the screen bounds
    container.contBox.x = clamp(
        int(container.contBox.x),
        0,
        GetScreenWidth() - int(container.contBox.width)
    );
    container.contBox.y = clamp(
        int(container.contBox.y),
        0,
        GetScreenHeight() - int(container.contBox.height)
    );
}

void Dialogue::CalculateContainerSize()
{
    container.contBox.width = static_cast<int>(GetScreenWidth() * 0.675);  // 67.5% of the screen width
    container.contBox.height = static_cast<int>(GetScreenHeight() * 0.2);  // 20% of the screen height
}