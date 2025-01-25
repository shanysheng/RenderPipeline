#ifndef PIPELINE_RENDERINGENGINE_H_GUARD
#define PIPELINE_RENDERINGENGINE_H_GUARD


#include "Common.h"


#include "RHIBuffer.h"
#include "RHISwapchain.h"
#include "RHIDevice.h"
#include "RHIGraphicPipeline.h"


#include "objModel.h"

namespace pipeline {




    // 创建vulkan应用所需要的windows
    // 创建vulkan instance实例，可以指定所需要的vulkan实例扩展
    // 根据window和instance，获取所需要的surface对象；
    // 选择物理设备对象
    // 创建逻辑设备对象，可以指定逻辑设备所需要的扩展接口，例如swapchain
    // 构建逻辑设备对应的swapchain、swapchainimage
    // 构建渲染framebuffer，framebuffer需要通过image view去操作swap chain image


    // command pool 包含 command buffer
    // command buffer 绑定render pass， frame buffer， graphic pipeline
    // render pass 指定 color attachment的操作方式
    // frame buffer指定swap chain中的image view -》swap chain对应的image
    // graphic pipeline指定fixed pipeline中的状态和shader module
    //

    // VkPipelineLayout，VkPipeline的功能差异
    // VkPipelineLayout包括VkDescriptorSetLayout和push const 
    // VkDescriptorSetLayout描述了通过VkDescriptorSetLayoutBinding描述VkPipelineLayout的Descriptor的布局；
    // 一般VkPipeline对应一个VkPipelineLayout，一个VkPipelineLayout对应一个或者多个VkDescriptorSetLayout；
    // 
    // VkDescriptorSet则是具体绘制过程（一个drawcall）对应的uniform buffer、textrue sampe等信息，通过VkDescriptorSetLayout布局进行穿件；
    // 每个drawcall，绑定VkPipeline和对应的VkPipelineLayout，以及具体VkDescriptorSet
    // 比如10个不同的模型采用同意个pipeline绘制，则会采用相同的VkPipeline和VkPipelineLayout，
    // 已经每个模型各自的VkDescriptorSet，其中包含了各自的sample、uniform buffer、shader storage buffer等特有参数


    // 渲染过程是异步的，获取swap chain image，执行command buffer，并把结果写入swap chain image，写入完成后可以进行present
    // 这里存在几个问题：
    // 1、获取swap chain image可能还在使用，需要等待被使用完；
    // 2、执行command buffer，执行完需要告知后续的流程，完成了写入；
    // 3、presnet流程的时候，需要等待被告知swap chain image已经写入完成，可以进行呈现；

    // 所以分成两个流程：渲染流程和呈现流程；
    // 渲染流程需要两个VkSemaphore：
    // 1、等待swap chain image获取成功，可以写入的imageAvailableSemaphore
    // 2、执行command buffer，渲染结果写入swap chain image完成，告知其他流程的renderFinishedSemaphore
    // 呈现流程需要一个VkSemaphore：
    // 1、swap chain image渲染结果写入完成，可被呈现renderFinishedSemaphore

    // 绘制流程：
    // 获取可用的swap chain image index；
    // reset command buffer
    // 开始记录command buffer（指定render pass、pipeline、image index指定的framebuffer）
    // 构建VkSubmitInfo，指定imageAvailableSemaphore和renderFinishedSemaphore，提交执行vkQueueSubmit
    // 
    // 呈现流程：
    // 构建VkPresentInfoKHR，指定renderFinishedSemaphore，vkQueuePresentKHR

    
    class IPreRender;
    class IRenderTarget;
    
    class kSGNode;
    class kScene;
    class kCamera;


    class kRenderQueueManager;
    class kRenderTargetManager;
    class kPreRenderManager;
    class kGPUResourceManager;
    class kRenderPipelineManager;
    
    class kWinInfo
    {
    public:
        kWinInfo() {
            pwindow = nullptr;
            width = 0;
            height = 0;
        }

        GLFWwindow* pwindow;
        uint32_t    width;
        uint32_t    height;
    };
    
    
    class kRenderingEngine
    {
    public:
        kRenderingEngine();
        virtual ~kRenderingEngine();

        //------------------------------------------------------------------------------
        //	Desc:	The function Configure configures the rendering engine 
        //			according to the config file, whose file name is the input 
        //			parameter ConfigFileName. When the string ConfigFileName is 
        //			empty or the file can not be found, the function uses the default 
        //			settings. This function should be called just after CRenderingEngine 
        //			object is constructed. OnConfigure as an over-writable function is 
        //			invoked in Configure, which gives developers opportunity to 
        //			configure rendering engine in desired way. If OnConfigure returns 
        //			non-zero value, the default configuration is skipped.
        //
        //------------------------------------------------------------------------------
        virtual int Configure(const std::string& ConfigFileName);

        //------------------------------------------------------------------------------
        //	Desc:	The function Initialize initializes the rendering engine when the 
        //			rendering output window is ready. It should not be invoked before 
        //			invoking the function Configure. The input parameter is a WinInfo 
        //			object, which specifies the parameters of the rendering output 
        //			window. 
        //
        //------------------------------------------------------------------------------
        virtual int Initialize(const kWinInfo& wininfo);

        //------------------------------------------------------------------------------
        //	Desc:	The function stops the render engine, and release the window 
        //			related resources allocated for the engine. When the engine is 
        //			finalized, the states inside the engine are set back to the 
        //			uninitialized but configured states. That is, after calling the 
        //			function Finalize, the function Initialize should be called again, 
        //			but no need to call the function Configure if the engine is to be 
        //			reused again. The destructor calls this function automatically. 
        //------------------------------------------------------------------------------
        virtual void Finalize();

        //------------------------------------------------------------------------------
        //	Desc:	The function OpenSceneModel is to open a scene model whose name
        //			is given by the input parameter SceneModelName, and set the 
        //			to-be-rendered scene graph. The string SceneModelName can be the 
        //			full path of the file, or just file name. When the string 
        //			SceneModelName is empty or the scene model can not be found in 
        //			default path, the function will return 0. It should be called 
        //			after calling Configure and Initialize. After executing 
        //			OpenSceneModel, the first kd-tree is regarded as the default 
        //			render traverse root. Moreover, according to the first kd-tree 
        //			(or the scene graph corresponding to the kd-tree), the engine's 
        //			internal camera is set to a set of default values. It means after 
        //			calling OpenSceneModel, developers can use GetCamera to retrieve 
        //			the default viewing parameters.
        //
        //	param:	SceneModelName is the full path of vdb, such as:J:\\a\\a.vdb
        //			
        //			return true if successful, else return false.			
        //------------------------------------------------------------------------------
        int OpenSceneModel(const std::string& SceneModelName, int ActiveSceneGraph = 0);
        void CloseSceneModel();


        //------------------------------------------------------------------------------
        //	Desc:	The function does all rendering tasks to generate one image in 
        //			the back frame buffer of the rendering output window, with respect 
        //			to the internal camera. By default, it renders the entities in the 
        //			active scene graph. For most walk-through application, the 
        //			application developers should call SetCamera and DoRendering at 
        //			certain rate with the changing viewing parameters. 
        //
        //------------------------------------------------------------------------------
        void ClearScreen(float r = 0.0f, float g = 0.3f, float b = 0.9f, float a = 0.0f);
        void DoRendering();
        void SwapBuffers();

        void FrameChanged() { m_FramebufferResized = true; }

    protected:

        void CreateSyncObjects();
        void CreateCommandBuffers();
        void BuildCommandBuffer(uint32_t imageIndex);

        void RecreateSwapChain();

        void SetRenderTraverseRoot( const std::vector<kSGNode*>& roots );
        void SetCamera(kCamera& Camera );
        void GetCamera(kCamera& Camera );
        
        
    protected:

        kRenderQueueManager*					GetRenderQueueManager()		{return m_pRenderQueueMgr;}
        kRenderTargetManager*					GetRenderTargetManager()	{return m_pRenderTargetMgr;}
        kPreRenderManager*						GetPreRenderManager()		{return m_pPreRenderMgr;}
        kGPUResourceManager*				    GetGPUResourceManager()	    {return m_pGPUResourceMpr;}
        kRenderPipelineManager*					GetRenderPipelineManager()	{return m_pRenderPipelineMgr;}
        
    protected:
        
        virtual int RegisterPreRenderPrototypes();
        virtual int RegisterRenderPipelinePrototypes();
        
        // user override functions
        virtual int OnConfigure();
        virtual int OnRegisterPreRenderPrototypes();
        virtual int OnRegisterRenderPipelinePrototypes();
        
    protected:
        
        kWinInfo								m_WinInfo;


        kRHIDevice						        m_Context;
        kRHISwapchain					        m_Swapchain;
        bool							        m_FramebufferResized = false;


        // Acquire an image from the swap chain
        // Execute commands that draw onto the acquired image
        // Present that image to the screen for presentation, returning it to the swapchain
        //
        // Semaphore
        // 
        // A semaphore is either unsignaled or signaled. It begins life as unsignaled. The way 
        // we use a semaphore to order queue operations is by providing the same semaphore as 
        // a 'signal' semaphore in one queue operation and as a 'wait' semaphore in another 
        // queue operation. For example, lets say we have semaphore S and queue operations A 
        // and B that we want to execute in order. What we tell Vulkan is that operation A will 
        // 'signal' semaphore S when it finishes executing, and operation B will 'wait' on 
        // semaphore S before it begins executing. When operation A finishes, semaphore S 
        // will be signaled, while operation B wont start until S is signaled. After operation 
        // B begins executing, semaphore S is automatically reset back to being unsignaled, 
        // allowing it to be used again.
        // Note that in this code snippet, both calls to vkQueueSubmit() return immediately - 
        // the waiting only happens on the GPU. The CPU continues running without blocking. 
        // To make the CPU wait, we need a different synchronization primitive, Fence.
        //
        // Fence
        //
        // A fence has a similar purpose, in that it is used to synchronize execution, but 
        // it is for ordering the execution on the CPU, otherwise known as the host. Simply 
        // put, if the host needs to know when the GPU has finished something, we use a fence.
        // A concrete example is taking a screenshot. Say we have already done the necessary 
        // work on the GPU. Now need to transfer the image from the GPU over to the host and 
        // then save the memory to a file. We have command buffer A which executes the transfer 
        // and fence F. We submit command buffer A with fence F, then immediately tell the host 
        // to wait for F to signal. This causes the host to block until command buffer A finishes 
        // execution. Thus we are safe to let the host save the file to disk, as the memory 
        // transfer has completed.
        // Unlike the semaphore example, this example does block host execution. This means the 
        // host won't do anything except wait until execution has finished. For this case, we 
        // had to make sure the transfer was complete before we could save the screenshot to disk.

        std::vector<VkSemaphore>		        m_ImageAvailableSemaphores;
        std::vector<VkSemaphore>		        m_RenderFinishedSemaphores;
        std::vector<VkFence>			        m_InFlightFences;
        std::vector<VkCommandBuffer>	        m_CommandBuffers;
        uint32_t						        m_CurrentFrame = 0;

        
        kGPUResourceManager*				    m_pGPUResourceMpr;
        kRenderQueueManager*   					m_pRenderQueueMgr;
        kRenderTargetManager*					m_pRenderTargetMgr;
        kPreRenderManager*						m_pPreRenderMgr;
        kRenderPipelineManager*					m_pRenderPipelineMgr;

        std::vector<kSGNode*>	                m_TraverseRoots;

        IPreRender*								m_pStartPreRender;
        IRenderTarget*						    m_pPrimeTarget;

    protected:

        kRHIGraphicPipeline				        m_GraphicPipeline;
        Model							        m_Model;
    };

}

#endif
