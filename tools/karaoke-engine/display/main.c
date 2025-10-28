#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codepoint;
    Vector2 position;
    int paragraphIndex;
} LyricGlyph;

float GetNextLineWidth(const char *text, int startByteOffset, Font font, int fontSize, float spacing, float screenWidth)
{
    float currentX = 0.0f;
    int textByteOffset = startByteOffset;

    while (text[textByteOffset] != '\0')
    {
        int codepointLength = 0;
        int codepoint = GetCodepoint(&text[textByteOffset], &codepointLength);

        if (codepoint == '\n')
        {
            break; 
        }

        GlyphInfo glyph = GetGlyphInfo(font, codepoint);
        float charWidth = glyph.advanceX + spacing;

        if (currentX + charWidth > screenWidth - 80 && currentX > 0) 
        {
            break; 
        }
        
        currentX += charWidth;
        textByteOffset += codepointLength;
    }
    
    return currentX;
}

void PrecalculateLayout(
    const char *text, Font font, int fontSize, float spacing, float lineSpacing, float screenWidth, float textStartY,
    LyricGlyph **outLayout, int *outLayoutCount,
    int **outParagraphStarts, int *outParagraphCount)
{
    if (*outLayout) free(*outLayout);
    if (*outParagraphStarts) free(*outParagraphStarts);

    *outLayoutCount = 0;
    *outLayout = NULL;
    *outParagraphCount = 1; 
    *outParagraphStarts = malloc(sizeof(int));
    (*outParagraphStarts)[0] = 0; 

    float lineStartX = (screenWidth - GetNextLineWidth(text, 0, font, fontSize, spacing, screenWidth)) / 2.0f;
    Vector2 position = { lineStartX, textStartY };
    int textByteOffset = 0;
    int currentParagraph = 0;

    while (text[textByteOffset] != '\0')
    {
        int codepointLength = 0;
        int codepoint = GetCodepoint(&text[textByteOffset], &codepointLength);

        if (codepoint == '\n')
        {
            lineStartX = (screenWidth - GetNextLineWidth(text, textByteOffset + codepointLength, font, fontSize, spacing, screenWidth)) / 2.0f;
            position.x = lineStartX;
            position.y += fontSize + lineSpacing;
            textByteOffset += codepointLength;
            
            currentParagraph++;
            (*outParagraphCount)++;
            *outParagraphStarts = realloc(*outParagraphStarts, sizeof(int) * (*outParagraphCount));
            (*outParagraphStarts)[currentParagraph] = *outLayoutCount; 

            continue;
        }

        GlyphInfo glyph = GetGlyphInfo(font, codepoint);
        float charWidth = glyph.advanceX + spacing;

        if (position.x + charWidth > screenWidth - 80 && position.x > lineStartX)
        {
            lineStartX = (screenWidth - GetNextLineWidth(text, textByteOffset, font, fontSize, spacing, screenWidth)) / 2.0f;
            position.x = lineStartX;
            position.y += fontSize + lineSpacing;
        }

        *outLayout = realloc(*outLayout, (*outLayoutCount + 1) * sizeof(LyricGlyph));
        LyricGlyph *g = &(*outLayout)[*outLayoutCount];
        
        g->codepoint = codepoint;
        g->position = position;
        g->paragraphIndex = currentParagraph;

        (*outLayoutCount)++;

        position.x += charWidth;
        textByteOffset += codepointLength;
    }
}

bool IsParagraphEmpty(int paragraphIndex, int *pStarts, int pCount, int gCount)
{
    if (paragraphIndex < pCount - 1) 
    {
        return pStarts[paragraphIndex] == pStarts[paragraphIndex + 1];
    }
    else 
    {
        return pStarts[paragraphIndex] == gCount;
    }
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }
    
    const char *filePath = argv[1]; 

    const int screenWidth = 1600; 
    const int screenHeight = 900; 
    const int fontSize = 72;
    const float spacing = 2.0f;
    const float lineSpacing = 10.0f;
    const float textStartY = 100.0f;
    const float middleScreenY = screenHeight / 2.0f;
    const int barHeight = 150; 
    
    InitWindow(screenWidth, screenHeight, "Hiragana Karaoke");
    
    Color bgColor = RAYWHITE;
    Color fgActive = BLACK;
    Color fgInactive = LIGHTGRAY;
    Color fgSeparator = GRAY;
    Color sliderInactive = LIGHTGRAY;
    Color sliderActive = MAROON;
    Color sliderHandle = RED;
    Color timeColor = LIGHTGRAY;
    Color titleColor = LIGHTGRAY; 

    char *configText = LoadFileText("config.txt");
    if (configText != NULL)
    {
        char *line;
        int r, g, b, a;
        line = strstr(configText, "BG=");
        if (line && sscanf(line, "BG=%d,%d,%d,%d", &r, &g, &b, &a) == 4) bgColor = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "FG_ACTIVE=");
        if (line && sscanf(line, "FG_ACTIVE=%d,%d,%d,%d", &r, &g, &b, &a) == 4) fgActive = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "FG_INACTIVE=");
        if (line && sscanf(line, "FG_INACTIVE=%d,%d,%d,%d", &r, &g, &b, &a) == 4) fgInactive = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "FG_SEPARATOR=");
        if (line && sscanf(line, "FG_SEPARATOR=%d,%d,%d,%d", &r, &g, &b, &a) == 4) fgSeparator = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "SLIDER_INACTIVE=");
        if (line && sscanf(line, "SLIDER_INACTIVE=%d,%d,%d,%d", &r, &g, &b, &a) == 4) sliderInactive = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "SLIDER_ACTIVE=");
        if (line && sscanf(line, "SLIDER_ACTIVE=%d,%d,%d,%d", &r, &g, &b, &a) == 4) sliderActive = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "SLIDER_HANDLE=");
        if (line && sscanf(line, "SLIDER_HANDLE=%d,%d,%d,%d", &r, &g, &b, &a) == 4) sliderHandle = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "TIME_COLOR=");
        if (line && sscanf(line, "TIME_COLOR=%d,%d,%d,%d", &r, &g, &b, &a) == 4) timeColor = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        line = strstr(configText, "TITLE_COLOR=");
        if (line && sscanf(line, "TITLE_COLOR=%d,%d,%d,%d", &r, &g, &b, &a) == 4) titleColor = (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
        UnloadFileText(configText);
    }
    else
    {
        printf("Warning: 'config.txt' not found. Using default colors.\n");
    }

    char *text = NULL;
    char *peerText = NULL;
    Font font = { 0 };
    Font peerFont = { 0 };

    LyricGlyph *layout = NULL;
    int layoutCount = 0;
    int *layoutParagraphStarts = NULL;
    int layoutParagraphCount = 0;

    LyricGlyph *peerLayout = NULL;
    int peerLayoutCount = 0;
    int *peerParagraphStarts = NULL;
    int peerParagraphCount = 0;
    
    LyricGlyph **activeLayout = NULL;
    int *activeLayoutCount = NULL;
    int **activeParagraphStarts = NULL;
    int *activeParagraphCount = NULL;
    Font *activeFont = NULL;

    bool showHiragana = false; 
    bool canSwitch = false;

    char peerFilePath[1024];
    const char *hiraganaSuffix = "-hiragana.txt";
    const char *kanjiSuffix = ".txt";
    
    if (strstr(filePath, hiraganaSuffix))
    {
        showHiragana = true;
        const char *suffixPos = strstr(filePath, hiraganaSuffix);
        int baseLen = suffixPos - filePath;
        snprintf(peerFilePath, 1024, "library/lyrics/%.*s%s", baseLen, filePath, kanjiSuffix);
    }
    else 
    {
        showHiragana = false;
        const char *suffixPos = strstr(filePath, kanjiSuffix);
        int baseLen = suffixPos - filePath;
        snprintf(peerFilePath, 1024, "library/lyrics-hiragana/%.*s%s", baseLen, filePath, hiraganaSuffix);
    }

    text = LoadFileText(filePath); 
    if (text == NULL)
    {
        CloseWindow();
        printf("Error: '%s' not found.\n", filePath);
        return 1;
    }
    
    peerText = LoadFileText(peerFilePath);
    canSwitch = (peerText != NULL);

    if (!canSwitch) printf("Warning: Peer lyric file '%s' not found. Switching disabled.\n", peerFilePath);

    int codepointCount = 0;
    int *codepoints = LoadCodepoints(text, &codepointCount);
    font = LoadFontEx("cousagi.ttf", fontSize, codepoints, codepointCount);
    UnloadCodepoints(codepoints);
    
    if (canSwitch)
    {
        int peerCodepointCount = 0;
        int *peerCodepoints = LoadCodepoints(peerText, &peerCodepointCount);
        peerFont = LoadFontEx("cousagi.ttf", fontSize, peerCodepoints, peerCodepointCount);
        UnloadCodepoints(peerCodepoints);
    }
    
    PrecalculateLayout(text, font, fontSize, spacing, lineSpacing, screenWidth, textStartY,
                       &layout, &layoutCount, &layoutParagraphStarts, &layoutParagraphCount);
    
    if (canSwitch)
    {
        PrecalculateLayout(peerText, peerFont, fontSize, spacing, lineSpacing, screenWidth, textStartY,
                           &peerLayout, &peerLayoutCount, &peerParagraphStarts, &peerParagraphCount);
    }

    const char *rawBaseName = GetFileNameWithoutExt(filePath);
    char baseName[256]; 
    strncpy(baseName, rawBaseName, 255);
    baseName[255] = '\0'; 
    const char *suffixToRemove = "-hiragana";
    int suffixLen = strlen(suffixToRemove);
    int baseLen = strlen(baseName);
    if (baseLen > suffixLen && strcmp(&baseName[baseLen - suffixLen], suffixToRemove) == 0)
    {
        baseName[baseLen - suffixLen] = '\0'; 
    }
    
    int titleCodepointCount = 0;
    int *titleCodepoints = LoadCodepoints(baseName, &titleCodepointCount);
    Font titleFont = LoadFontEx("PopRumKiwi-Telop.otf", 100, titleCodepoints, titleCodepointCount); 
    UnloadCodepoints(titleCodepoints); 

    if (titleFont.texture.id == 0) {
        printf("Warning: Could not load title font 'cousagi.ttf'. Using default.\n");
        titleFont = GetFontDefault();
    }

    InitAudioDevice();
    char musicPath[1024];
    snprintf(musicPath, 1024, "library/music/%s.mp3", baseName); 
    Music music = LoadMusicStream(musicPath);
    bool musicLoaded = (music.stream.buffer != NULL);
    float musicLength = 0.0f;

    if (musicLoaded)
    {
        PlayMusicStream(music);
        musicLength = GetMusicTimeLength(music);
    }
    else
    {
        printf("Warning: Could not load music file: %s\n", musicPath);
    }
    bool musicPaused = false;
    
    if (showHiragana) 
    {
        activeLayout = &layout;
        activeLayoutCount = &layoutCount;
        activeParagraphStarts = &layoutParagraphStarts;
        activeParagraphCount = &layoutParagraphCount;
        activeFont = &font;
    }
    else 
    {
        if (canSwitch) 
        {
            activeLayout = &peerLayout;
            activeLayoutCount = &peerLayoutCount;
            activeParagraphStarts = &peerParagraphStarts;
            activeParagraphCount = &peerParagraphCount;
            activeFont = &peerFont;
            
            showHiragana = false; 
        }
        else 
        {
            activeLayout = &layout;
            activeLayoutCount = &layoutCount;
            activeParagraphStarts = &layoutParagraphStarts;
            activeParagraphCount = &layoutParagraphCount;
            activeFont = &font;
            
            showHiragana = true; 
        }
    }
    
    int currentParagraphIndex = 0; 
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth / 2.0f, middleScreenY };
    camera.target = (Vector2){ screenWidth / 2.0f, textStartY };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    Rectangle sliderBar = { 70, screenHeight - 60, screenWidth - 140, 20 };
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        
        if (musicLoaded)
        {
            if (!musicPaused) UpdateMusicStream(music);
            if (IsKeyPressed(KEY_ENTER))
            {
                musicPaused = !musicPaused;
                if (musicPaused) PauseMusicStream(music);
                else ResumeMusicStream(music);
            }
            if (IsKeyPressed(KEY_R))
            {
                StopMusicStream(music);
                PlayMusicStream(music);
                currentParagraphIndex = 0; 
            }
            if (IsKeyPressed(KEY_LEFT))
            {
                float currentTime = GetMusicTimePlayed(music);
                float newTime = currentTime - 5.0f;
                if (newTime < 0) newTime = 0;
                SeekMusicStream(music, newTime);
            }
            if (IsKeyPressed(KEY_RIGHT))
            {
                float currentTime = GetMusicTimePlayed(music);
                float newTime = currentTime + 5.0f;
                if (newTime > musicLength) newTime = musicLength - 0.1f; 
                SeekMusicStream(music, newTime);
            }
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, sliderBar))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && GetMouseDelta().x != 0))
                {
                    float mouseX = mousePos.x - sliderBar.x;
                    float seekFraction = mouseX / sliderBar.width;
                    if (seekFraction < 0) seekFraction = 0;
                    if (seekFraction > 1) seekFraction = 1;
                    SeekMusicStream(music, seekFraction * musicLength);
                }
            }
        }
        
        if (IsKeyPressed(KEY_Q) && canSwitch)
        {
            showHiragana = !showHiragana;
            if (showHiragana)
            {
                activeLayout = &layout;
                activeLayoutCount = &layoutCount;
                activeParagraphStarts = &layoutParagraphStarts;
                activeParagraphCount = &layoutParagraphCount;
                activeFont = &font;
            }
            else
            {
                activeLayout = &peerLayout;
                activeLayoutCount = &peerLayoutCount;
                activeParagraphStarts = &peerParagraphStarts;
                activeParagraphCount = &peerParagraphCount;
                activeFont = &peerFont;
            }
        }

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_SPACE)) 
        {
            if (currentParagraphIndex < *activeParagraphCount - 1) 
            {
                int newIndex = currentParagraphIndex + 1;
                
                while (newIndex < *activeParagraphCount - 1 && 
                       IsParagraphEmpty(newIndex, *activeParagraphStarts, *activeParagraphCount, *activeLayoutCount))
                {
                    newIndex++;
                }
                
                if (IsParagraphEmpty(newIndex, *activeParagraphStarts, *activeParagraphCount, *activeLayoutCount))
                {
                    currentParagraphIndex = 0; 
                    if (musicLoaded) { StopMusicStream(music); PlayMusicStream(music); }
                }
                else
                {
                    currentParagraphIndex = newIndex; 
                }
            } 
            else 
            {
                currentParagraphIndex = 0;
                if (musicLoaded) { StopMusicStream(music); PlayMusicStream(music); }
            }
        }
        
        if (IsKeyPressed(KEY_BACKSPACE)) 
        {
             if (currentParagraphIndex > 0)
             {
                 int newIndex = currentParagraphIndex - 1;
                 
                 while (newIndex > 0 &&
                        IsParagraphEmpty(newIndex, *activeParagraphStarts, *activeParagraphCount, *activeLayoutCount))
                 {
                     newIndex--;
                 }
                 
                 currentParagraphIndex = newIndex;
             }
        }
        
        
        Vector2 targetCharPos = { screenWidth / 2.0f, textStartY };
        if (*activeLayout && *activeParagraphCount > currentParagraphIndex)
        {
            int startGlyphIndex = (*activeParagraphStarts)[currentParagraphIndex];
            if (startGlyphIndex < *activeLayoutCount)
            {
                targetCharPos = (*activeLayout)[startGlyphIndex].position;
            }
        }
        
        float lerpSpeed = 8.0f * GetFrameTime(); 
        if (lerpSpeed > 1.0f) lerpSpeed = 1.0f;
        camera.target.y = Lerp(camera.target.y, targetCharPos.y, lerpSpeed);
        camera.target.x = screenWidth / 2.0f; 
        
        BeginDrawing();
        ClearBackground(bgColor);
        
        BeginMode2D(camera);
        {
            for (int i = 0; i < *activeLayoutCount; i++)
            {
                LyricGlyph *g = &(*activeLayout)[i];
                Color color;

                if (g->codepoint == '/')
                {
                    color = fgSeparator;
                }
                else
                {
                    color = (g->paragraphIndex <= currentParagraphIndex) ? fgActive : fgInactive;
                }
                
                DrawTextCodepoint(*activeFont, g->codepoint, g->position, fontSize, color);
            }
        }
        EndMode2D(); 

        DrawRectangle(0, 0, screenWidth, barHeight, BLACK);
        DrawRectangle(0, screenHeight - barHeight, screenWidth, barHeight, BLACK);
        
        DrawTextEx(titleFont, baseName, (Vector2){ 20, 25 }, titleFont.baseSize, 1.0f, titleColor);
        
        char timeElapsedStr[16] = "00:00";
        char timeTotalStr[16] = "00:00";
        float progress = 0.0f;

        if (musicLoaded)
        {
            float elapsed = GetMusicTimePlayed(music);
            if (musicLength > 0) progress = elapsed / musicLength;
            snprintf(timeElapsedStr, 16, "%02d:%02d", (int)elapsed / 60, (int)elapsed % 60);
            snprintf(timeTotalStr, 16, "%02d:%02d", (int)musicLength / 60, (int)musicLength % 60);

            DrawRectangleRec(sliderBar, sliderInactive); 
            DrawRectangleRec((Rectangle){ sliderBar.x, sliderBar.y, sliderBar.width * progress, sliderBar.height }, sliderActive); 
            DrawRectangleRec((Rectangle){ sliderBar.x + sliderBar.width * progress - 4, sliderBar.y - 5, 8, sliderBar.height + 10 }, sliderHandle);
        }

        DrawText(timeElapsedStr, 10, screenHeight - 60, 20, timeColor);
        int totalTimeWidth = MeasureText(timeTotalStr, 20);
        DrawText(timeTotalStr, screenWidth - totalTimeWidth - 10, screenHeight - 60, 20, timeColor);

        EndDrawing();
    }

    UnloadFileText(text);
    if (peerText) UnloadFileText(peerText);
    
    if (layout) free(layout);
    if (layoutParagraphStarts) free(layoutParagraphStarts);
    if (peerLayout) free(peerLayout);
    if (peerParagraphStarts) free(peerParagraphStarts);

    UnloadFont(font);
    if (peerFont.texture.id != 0) UnloadFont(peerFont);

    if (titleFont.texture.id != GetFontDefault().texture.id) UnloadFont(titleFont);
    if (musicLoaded) UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
