#pragma once

#include <functional>
#include <list>

namespace chroma
{
	// An Event Handler is the Subscriber to an Event that calls a Function when notified by the Event
	template <typename... Args> class EventHandler
	{
	public:
		typedef std::function<void(Args...)> functionType;
		typedef unsigned int handlerId;

		explicit EventHandler(const functionType& function) : m_Function(function)
		{
			m_Id = ++idCounter;
		}

		// -- Operator
		void operator()(Args... params) const
		{
			if (m_Function)
				m_Function(params...);
		}

		bool operator==(const EventHandler& other) const
		{
			return m_Id == other.m_Id;
		}

		// -- Getter
		handlerId GetID() const
		{
			return m_Id;
		}

	private:
		// ID of the Handler
		handlerId m_Id;

		// Function that gets called when notified
		functionType m_Function;

		// TODO: Make Thead-Safe
		static unsigned int idCounter;
	};

	template <typename... Args> unsigned int EventHandler<Args...>::idCounter;

	template <typename... Args> class Event
	{
	public:
		typedef EventHandler<Args...> eventHandlerType;

		void Subscribe(const EventHandler<Args...>& subscriber) const
		{
			m_Handlers.push_back(subscriber);
		}

		void Unsubscribe(const EventHandler<Args...>& subscriber) const
		{
			auto it = std::find(m_Handlers.begin(), m_Handlers.end(), subscriber);
			if (it != m_Handlers.end())
				m_Handlers.erase(it);
		}

		void Dispatch(Args... params) const
		{
			for (const auto& subscriber : m_Handlers)
			{
				subscriber(params...);
			}
		}

		// -- Operator(For Usage Convenience)
		void operator+=(const EventHandler<Args...>& other)
		{
			Subscribe(other);
		}

		void operator-=(const EventHandler<Args...>& other)
		{
			Unsubscribe(other);
		}

	private:
		std::list<eventHandlerType> m_Handlers;
	};
}