#pragma once

#include <atomic>
#include <functional>  
#include <pulse/pulseaudio.h>
#include <EyesView.h>
#include <Surface.h>
#include <NetworkClient.h>
#include <MediaClient.h>
#include <MicAudioStreamingUseCase.h>
#include <MicButtonListenerUseCase.h>
#include <ManageEyesStateUseCase.h>
#include <SpeakerAudioStreamingUseCase.h>
#include <ShutdownListenerUseCase.h>
#include <Semaphore.h>
#include <mutex>
#include <thread>
#include <queue>

using namespace std; 

class App {
    private:
        mutex mtx;
        condition_variable cv;
        queue<function<void()>> q;
        atomic<bool> isCancelled;
        
        atomic<pa_threaded_mainloop*> loop;
        Surface surface;
        EyesView view;

        ShutdownListenerUseCase shutdownListenerUseCase;
        ManageEyesStateUseCase manageEyesStateUseCase;
        MicAudioStreamingUseCase micAudioStreamingUseCase;
        SpeakerAudioStreamingUseCase speakerAudioStreamingUseCase;
        
        NetworkClient networkClient;
        MediaClient mediaClient;

         atomic<bool> firstCallReceived{false};

    public:
        static App& instance(); 

        App();
        void start();
        void run();
        MediaClient* getMediaClient();
        ~App();
};