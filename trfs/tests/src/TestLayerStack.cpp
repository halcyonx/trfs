#include <gtest/gtest.h>
#include <Core/Layer.h>
#include <Core/LayerStack.h>

TEST(TestLayerStack, TestPushAndPopLayer)
{
	using namespace Core;
	LayerStack stack;

	// Mock layer for testing
	Layer *layer = new Layer("TestLayer");

	// Push layer and verify increase in size
	stack.PushLayer(layer);
	EXPECT_EQ(stack.GetFirst()->GetName(), "TestLayer");

	// Pop layer and verify decrease in size
	stack.PopLayer(layer);
	EXPECT_EQ(stack.begin(), stack.end());

	delete layer;
}

TEST(TestLayerStack, TestPushAndPopOverlay)
{
	using namespace Core;
	LayerStack stack;

	// Mock overlay for testing
	Layer *overlay = new Layer("TestOverlay");

	// Push overlay and verify increase in size
	stack.PushOverlay(overlay);
	EXPECT_EQ(stack.GetLast()->GetName(), "TestOverlay");

	// Pop overlay and verify decrease in size
	stack.PopOverlay(overlay);
	EXPECT_EQ(stack.GetLayers().size(), 0);

	delete overlay;
}

TEST(TestLayerStack, TestGetFirstAndLast)
{
	using namespace Core;
	LayerStack stack;

	// Mock layers for testing
	Layer *layer1 = new Layer("TestLayer1");
	Layer *layer2 = new Layer("TestLayer2");
	Layer *layer3 = new Layer("TestLayer3");

	// Push layers and verify first and last
	stack.PushLayer(layer1);
	stack.PushLayer(layer2);
	stack.PushLayer(layer3);
	EXPECT_EQ(stack.GetFirst()->GetName(), "TestLayer1");
	EXPECT_EQ(stack.GetLast()->GetName(), "TestLayer3");

	// Pop layers and verify first and last
	stack.PopLayer(layer3);
	stack.PopLayer(layer2);
	stack.PopLayer(layer1);
	EXPECT_EQ(stack.GetLayers().size(), 0);

	delete layer1;
	delete layer2;
	delete layer3;
}