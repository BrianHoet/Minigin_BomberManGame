#include <stdexcept>
#include "Renderer.h"

#include <chrono>
#include <iostream>

#include "SceneManager.h"
#include "Texture2D.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl2.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_plot.h"

struct Transform
{
	float matrix[16] = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};
class GameObject3D
{
public:
	Transform transform;
	int ID{};
};
class GameObject3DAlt
{
public:
	~GameObject3DAlt()
	{
		delete transform;
	}
	Transform* transform;
	int ID;
};

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void RenderStats(float min, float max, const float** data, int values, ImU32* colors, int count = 1)
{
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.ys_list = data;
	conf.values.ys_count = count;
	conf.values.count = values;
	conf.line_thickness = 2.f;
	conf.values.colors = colors;
	conf.scale.min = min;
	conf.scale.max = max;
	conf.tooltip.show = true;
	conf.frame_size = ImVec2(250, 100.f);
	conf.line_thickness = 2.f;

	ImGui::Plot("plot", conf);
}
void RenderStats(std::vector<float> data, int values, ImU32& color)
{
	auto minIt = std::min_element(data.begin(), data.end());
	auto maxIt = std::max_element(data.begin(), data.end());
	float min = *minIt;
	float max = *maxIt;

	const float* dataFl[]{ {&data[0]} };
	ImU32 colors[1]{ {color} };

	RenderStats(min, max, dataFl, values, colors);
}

void GenerateDataTrashCache(int& size, int steps, std::vector<float>& timesFl)
{
	
	const int length = 10'000'000;
	int* array = new int[length] {};
	
	for (int stepsize = 1; stepsize <= (1024 * steps); stepsize *= 2)
	{
		float minTime{};
		float maxTime{};
		std::vector<float> times{};
	
		for (int sample{}; sample < 10; ++sample)
		{
	
			auto start = std::chrono::high_resolution_clock::now();
	
			for (int i = 0; i < length; i += stepsize)
			{
				array[i] *= 2;
			}
	
			auto end = std::chrono::high_resolution_clock::now();
			const float elapsedTime = float(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	
			if (elapsedTime > maxTime)
				maxTime = elapsedTime;
	
			else if (elapsedTime < minTime)
				minTime = elapsedTime;
	
			times.push_back(elapsedTime);
		}
	
		times.erase(std::remove(times.begin(), times.end(), minTime), times.end());
	
		times.erase(std::remove(times.begin(), times.end(), maxTime), times.end());
	
		float avgTime{};
		for (auto t : times)
		{
			avgTime += t;
		}
		avgTime /= times.size();
	
		std::cout << avgTime / 1000.f << "\n";
	
		timesFl.push_back(avgTime);
	
	}
	
	size = int(timesFl.size());

}
void GenerateDataTrashCacheGameObject3D(int& size, int, std::vector<float>& timesFl)
{
	static float data[10]{};
	const int bufferSize{ 1'000'000 };
	std::vector<GameObject3D*>buffer{};
	buffer.resize(bufferSize);
	std::vector<long long> times{};
	int index{};
	do
	{
		buffer[index] = new GameObject3D();
		buffer[index]->ID = 100;
		++index;
	} while (index < bufferSize);

	int stepSize{};
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i{}; i < bufferSize; i += stepSize)
		{
			buffer[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
		times.emplace_back(elapsedTime);
	}
	size = static_cast<int>(times.size());
	for (int i{}; i < size; ++i)
	{
		timesFl.emplace_back(static_cast<float>(times[i]));
	}

	for (auto object : buffer)
	{
		delete object;
	}
}
void GenerateDataTrashCacheGameObject3DAlt(int& size, int, std::vector<float>& timesFl)
{
	static float data[10]{};
	const int bufferSize{ 1'000'000 };
	std::vector<GameObject3DAlt*>buffer{};
	buffer.resize(bufferSize);
	std::vector<long long> times{};
	int index{};
	do
	{
		buffer[index] = new GameObject3DAlt();
		buffer[index]->ID = 100;
		buffer[index]->transform = new Transform();
		++index;
	} while (index < bufferSize);

	int stepSize{};
	for (stepSize = 1; stepSize <= 1024; stepSize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i{}; i < bufferSize; i += stepSize)
		{
			buffer[i]->ID *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto elapsedTime = duration_cast<std::chrono::microseconds>(end - start).count();
		times.emplace_back(elapsedTime);
	}

	size = static_cast<int>(times.size());
	for (int i{}; i < size; ++i)
	{
		data[i] = static_cast<float>(times[i]);
	}

	for (int i{}; i < size; ++i)
	{
		timesFl.emplace_back(static_cast<float>(times[i]));
	}

	for (auto object : buffer)
	{
		delete object;
	}
}

void dae::Renderer::Render()
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	
	//DrawPlotTrashCache();
	//DrawPlotGameObject3D();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

void dae::Renderer::DrawPlotTrashCache()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
	static char   u8_v = 100;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImGui::InputScalar("amount of samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_IndexSteps = static_cast<int>(u8_v);
	const char* buttonText = "Trash the cache";
	if (ImGui::Button(buttonText))
	{
		ImGui::Text("Generating data ...");
		m_TrashCacheDataSize = 0;
		GenerateDataTrashCache(m_TrashCacheDataSize, m_IndexSteps, m_TrashCacheData);
	}

	if (m_TrashCacheDataSize > 0)
	{
		ImU32 colorYellow = { ImColor{255,255,0} };
		RenderStats(m_TrashCacheData, m_TrashCacheDataSize, colorYellow);
	}
	ImGui::End();
}
void dae::Renderer::DrawPlotGameObject3D()
{
	static char   u8_v = 100;
	static char   u8_one = 1;
	static ImU8   u8_min = 0;
	static ImU8   u8_max = 255;
	ImU32 colorGreen = { ImColor{0,255,0} };
	ImU32 colorBlue = { ImColor{0,0,225} };
	const bool size3DBigger0 = m_TrashCacheDataSizeObject3D > 0;
	const bool sizeAlt3DBigger0 = m_SizeObject3DAlt > 0;


	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);
	ImGui::InputScalar("amount of samples", ImGuiDataType_U8, &u8_v, &u8_one, NULL, "%u");
	m_IndexObject3D = static_cast<int>(u8_v);
	const char* TextButton = "GameObject3D";
	if (ImGui::Button(TextButton))
	{
		ImGui::Text("Generating data ...");
		m_TrashCacheDataSizeObject3D = 0;
		GenerateDataTrashCacheGameObject3D(m_TrashCacheDataSizeObject3D, m_IndexObject3D, m_TrashCacheDataObject3D);
	}

	if (size3DBigger0)
	{
		RenderStats(m_TrashCacheDataObject3D, m_TrashCacheDataSizeObject3D, colorGreen);
	}

	TextButton = "GameObject3DAlt";
	if (ImGui::Button(TextButton))
	{
		ImGui::Text("Generating data ...");
		m_SizeObject3DAlt = 0;
		GenerateDataTrashCacheGameObject3DAlt(m_SizeObject3DAlt, m_IndexObject3D, m_TrashCacheDataObject3DAlt);
	}

	if (sizeAlt3DBigger0)
	{
		RenderStats(m_TrashCacheDataObject3DAlt, m_SizeObject3DAlt, colorBlue);
	}

	if (size3DBigger0 && sizeAlt3DBigger0)
	{
		float min3D = *std::min_element(m_TrashCacheDataObject3D.begin(), m_TrashCacheDataObject3D.end());
		float max3D = *std::max_element(m_TrashCacheDataObject3D.begin(), m_TrashCacheDataObject3D.end());
		float min3DAlt = *std::min_element(m_TrashCacheDataObject3DAlt.begin(), m_TrashCacheDataObject3DAlt.end());
		float max3DAlt = *std::max_element(m_TrashCacheDataObject3DAlt.begin(), m_TrashCacheDataObject3DAlt.end());

		float min = min3D < min3DAlt ? min3D : min3DAlt;
		float max = max3D > max3DAlt ? max3D : max3DAlt;
		const int totalAllowdArrayValues{ 2 };
		const float* dataFl[totalAllowdArrayValues]{ &m_TrashCacheDataObject3D[0],&m_TrashCacheDataObject3DAlt[0] };
		ImU32 colors[totalAllowdArrayValues]{ colorGreen,colorBlue };

		RenderStats(min, max, dataFl, 10, colors, 2);
	}
	ImGui::End();
}
