//------------------------------------------------------------------------------
/*
  LayerEffects for JUCE

  Official project location:
  https://github.com/vinniefalco/LayerEffects

  ------------------------------------------------------------------------------

  License: MIT License (http://www.opensource.org/licenses/mit-license.php)
  Copyright (c) 2012 by Vinnie Falco

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/
//------------------------------------------------------------------------------

#include "AppConfig.h"

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parameter
#pragma warning (disable: 4355) // 'this' used in base member intializer list
#endif

#include "modules/juce_core/juce_core.h"
#include "modules/juce_gui_basics/juce_gui_basics.h"
#include "modules/juce_gui_extra/juce_gui_extra.h"

#include "modules/vf_core/vf_core.h"
#include "modules/vf_gui/vf_gui.h"
#include "modules/vf_unfinished/vf_unfinished.h"

using namespace juce;

#include "gui/Controls.h"
#include "gui/CustomLookAndFeel.h"
#include "gui/Options.h"
#include "gui/CSolidColourPicker.h"

#include "gui/CBackgroundPanel.h"
#include "gui/CImageDropTarget.h"
#include "gui/COptionsTab.h"
#include "gui/CBevelEmbossTab.h"
#include "gui/CDropShadowTab.h"
#include "gui/CGradientOverlayTab.h"
#include "gui/COptionsFillTab.h"
#include "gui/COptionsGeneralTab.h"
#include "gui/COptionsPanel.h"
#include "gui/CLayerGraphicsPreview.h"
#include "gui/CMainPanel.h"
#include "gui/CMainWindow.h"

#include "gui/MainApp.h"

//----------

#include "gui/Controls.cpp"
#include "gui/CustomLookAndFeel.cpp"
#include "gui/MainApp.cpp"
#include "gui/Options.cpp"
#include "gui/CSolidColourPicker.cpp"

#include "gui/CBackgroundPanel.cpp"
#include "gui/CBevelEmbossTab.cpp"
#include "gui/CGradientOverlayTab.cpp"
#include "gui/CImageDropTarget.cpp"
#include "gui/CDropShadowTab.cpp"
#include "gui/CLayerGraphicsPreview.cpp"
#include "gui/CMainPanel.cpp"
#include "gui/CMainWindow.cpp"
#include "gui/COptionsFillTab.cpp"
#include "gui/COptionsGeneralTab.cpp"
#include "gui/COptionsPanel.cpp"
#include "gui/COptionsTab.cpp"

#ifdef _MSC_VER
#pragma warning (pop)
#endif
