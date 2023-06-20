#include "dialogue.h"

#include "nlohmann/json.hpp"
#include <cstdio>
#include <exception>
#include <fstream>
#include <iostream>
#include <raylib.h>

// Constructor
Dialogue::Dialogue()
{
    currentNodeID   = -1;
    dialogueFinished= false;
    removedCharacters = "";
}

// Deconstuctor
Dialogue::~Dialogue() {}


// Dialogue Functions
void Dialogue::LoadDialogue(const std::string &filepath)
{
    // Read JSON dialogue file
    std::ifstream jsdaFile(filepath);
    if (!jsdaFile.fail()) {
        std::cerr << filepath << "was not successfully opened.\n Please check that the file currently exists.\n";
        exit(1);
    }

    nlohmann::json jsonData;

    try { jsdaFile >> jsonData; }
    catch (const nlohmann::json::parse_error &e) {
        jsdaFile.close();
        std::cerr << "JSON parse error: " << e.what() << "\n";
        exit(1);
    }

    for (const auto &[nodeID, nodeData] : jsonData.items()) {
        DialogueNode dnode;
        dnode.character = nodeData["character"];
        dnode.dialogue = nodeData["dialogue"];

        // Check if node contains repsonses
        if (nodeData.find("responses") != nodeData.end()) {
            for (const auto &[responseText, response] : nodeData["responses"].items()) {
                std::string nextNodeID = response["next"];
                dnode.nextNodeID.push_back(std::stoi(nextNodeID));
            }
        }

        // Add dialogue to vector
        node.push_back(dnode);
    }

    jsdaFile.close();
}

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
    // Set containerSX to be 67.5% of the screen width
    container.contBox.width = static_cast<float>(GetScreenWidth() * 0.675);
    // Set containerSY to be 20% of the screen height
    container.contBox.height = static_cast<float>(GetScreenHeight() * 0.2);
}

void Dialogue::SetImage(const Texture2D& imageTexture)
{
    container.charImage = imageTexture;

    // Set imageSX to be 18.52% of container
    container.charImage.width = static_cast<float>(container.contBox.width * 0.1852);
    // Set imageSY to be 83.3% of container
    container.charImage.height = static_cast<float>(container.contBox.height * 0.8333);

    // Set imagePX to be 1.85% of container
    container.imagePosition.x = static_cast<float>(container.contBox.width * 0.0185);
    // Set imagePY to be 8.3% of container
    container.imagePosition.x = static_cast<float>(container.contBox.width * 0.083);

}

void Dialogue::CreateTextbox()
{
    // Set textboxSX to be 76% of container
    container.textBox.width = static_cast<float>(container.contBox.width * 0.76);
    // Set textboxSY to be 83.3% of container
    container.textBox.height = static_cast<float>(container.contBox.height * 0.8333);


    // Set textboxPX to be 24% of container
    container.textBox.x = static_cast<float>(container.contBox.width * 0.24);
    // Set textboxPY to be 8.3% of container
    container.textBox.y = static_cast<float>(container.contBox.height * 0.083);
}

void Dialogue::DrawDialogueText(const int fontSize)
{
    // Get current dialogue node
    const DialogueNode &currentNode = node[currentNodeID];

    // Truncate the dialogue text to fit within the textbox
    std::string dialogueText = removedCharacters + " " + currentNode.dialogue;
    const float maxLineLength = container.textBox.width - 20.0f;

    if (MeasureText(dialogueText.c_str(), fontSize) > maxLineLength) {
        while (MeasureText(dialogueText.c_str(), fontSize) > maxLineLength) {
            removedCharacters = dialogueText.substr(dialogueText.length() - 1) + removedCharacters;
            dialogueText = dialogueText.substr(0, dialogueText.length() - 1);
        }
        dialogueText += "...";
    }

    //Draw truncated dialogue text
    //TODO: draw text
}