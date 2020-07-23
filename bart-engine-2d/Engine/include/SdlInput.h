#pragma once

#include <IInput.h>

namespace bart
{
	class SdlInput final : public IInput
	{
	public:
		virtual ~SdlInput() = default;

		bool Initialize() override;
		void Destroy() override;
		void PoolEvents() override;
		bool IsKeyDown(EKeys key) override;
		bool IsMouseButtonDown(EMouseButton button) override;
		void GetMousePosition(int* x, int* y) override;

	private:
		void CheckMouseButton(unsigned char button, bool state);

		unsigned char* m_KeyUpStates = nullptr;
		const unsigned char* m_KeyDownState = nullptr;
		int m_MouseX = 0;
		int m_MouseY = 0;
		bool m_MouseStates[3]{false, false, false};
	};
}
