#ifdef __linux__
#include "DrmController.h"
#include "CommonApi.h"
#include <thread>
#include <mutex>
#ifdef __linux__
   #include <fcntl.h>
   #include <xf86drm.h>
   #include <xf86drmMode.h>
   #include <boost/property_tree/ptree.hpp>  
   #include <boost/property_tree/ini_parser.hpp>  
#endif

#define DRM_DIVICE_CARD0   "/dev/dri/card0"

/**
* @brief  The Drm parameters to display.
* @detail To set the drm display parameters.
*/
struct DrmDisplayDev {
  struct DrmDisplayDev *next;

   uint32_t width;
	uint32_t height;
	uint32_t stride;
	size_t size;
	uint32_t handle;
	uint8_t *map;
	uint32_t plane_id;

	drmModeModeInfo mode;
	uint32_t fb;
	uint32_t conn;
	int crtc;
	drmModeCrtc *saved_crtc;
};

static void unDisplay(int fd, uint32_t planeid) {

   drmModePlanePtr plane = drmModeGetPlane(fd, planeid);
   if (!plane) {
      consolePrint("Get plane failed...");
   }

    // Set CRTC_ID NUll to close the output.  
    uint64_t crtc_id = 0;  
    if (drmModeSetPlane(fd, planeid, crtc_id, 0, 0, 0, 0, 0,0,0,0,0,0) < 0) {  
        consolePrint("drmModeSetPlane %d failed ",  planeid);  
        //exit(EXIT_FAILURE);  
    }  
    consolePrint("unDisplay ok planeid: %d", planeid);

   if(plane) {
      drmModeFreePlane(plane);
   }
}

bool DrmController::init()
{
/* open the DRM device */
int ret = drmdisplayOpen(&m_fd, DRM_DIVICE_CARD0);
if (ret) {
   consolePrint( "drmdisplay modeset_open fail\n");
   if (ret) {
      errno = -ret;
      consolePrint("modeset failed with error %d: %m\n", errno);
   } else {
      consolePrint("exiting\n");
   }
   return ret;
}

if(!initWithIni()) {
   consolePrint("Init drm ini failed...");
}

if(!initPlane()) {
      consolePrint("Init plane failed ...");
      return false;
}

/* prepare all connectors and CRTCs */
ret = drmdisplayPrepare();
if (ret) {
   consolePrint("drmdisplay drmdisplay_prepare fail\n");
   close(m_fd);
   return ret;
}
/* perform actual modesetting on each found connector+CRTC */
for (DrmDisplayDev* iter = m_drmdisplayList; iter; iter = iter->next) {
   iter->saved_crtc = drmModeGetCrtc(m_fd, iter->crtc);
   consolePrint("saved_crtc id:%d width:%d height:%d mode_name:%s", iter->saved_crtc->crtc_id, iter->saved_crtc->width, iter->saved_crtc->height, iter->saved_crtc->mode.name);
   ret = drmModeSetCrtc(m_fd, iter->crtc, iter->fb, 0, 0,
               &iter->conn, 1, &iter->mode);
   if (ret)
      consolePrint("cannot set CRTC for connector %u (%d)", iter->conn);
}

 return true;
}

bool DrmController::initPlane()
{
   if(m_fd <= 0) return false;
   drmSetClientCap(m_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
   drmModePlaneRes* planeRes = drmModeGetPlaneResources(m_fd);
   if(!planeRes){
      consolePrint("Get plane resourses failed ...");
      drmdisplayCleanup();
      return false;
   }
   consolePrint("m_planeRes->count_planes %d", planeRes->count_planes);
   for (size_t i = 0; i < planeRes->count_planes; i++)
   {
      drmModePlane* pPlane = drmModeGetPlane(m_fd, planeRes->planes[i]);
      consolePrint("---Plane plane_id %u ----", pPlane->plane_id);
      
      if (pPlane &&  pPlane->crtc_id == 0 && (pPlane->possible_crtcs & 1))
      {
         consolePrint("Plane crtc_id %u ", pPlane->crtc_id);
         consolePrint("Plane fb_id %u ", pPlane->fb_id);
         consolePrint("Plane plane_id %u ", pPlane->plane_id);
         consolePrint("Plane count_formats %u ", pPlane->count_formats);
         consolePrint("Plane possible_crtcs %u ", pPlane->possible_crtcs);
         
         // Get plane's properties.
         drmModeObjectProperties* props = drmModeObjectGetProperties(m_fd, pPlane->plane_id, DRM_MODE_OBJECT_PLANE);
         if (!props) {
            consolePrint("Failed to get plane properties");
            drmdisplayCleanup();
            drmModeFreePlane(pPlane);
            drmModeFreePlaneResources(planeRes);
            return false;
         }

         uint64_t zpos = 20;
         for (int j = 0; j < props->count_props; j++) {
            drmModePropertyRes* prop = drmModeGetProperty(m_fd, props->props[j]);
            consolePrint("------------------------------------props name:%s prop id: %d flags: %llu value: [%d] :%llu-----------------------------------------", prop->name, prop->prop_id, prop->flags, props->prop_values[j]);
            if (prop && strcmp(prop->name, "zpos") == 0 && (pPlane->plane_id == m_arrayDrmIniConf[1].plane_id)) {

                  drmModeObjectSetProperty(m_fd, pPlane->plane_id, DRM_MODE_OBJECT_PLANE, prop->prop_id, m_arrayDrmIniConf[1].plane_zpos);
                  consolePrint("-----------------------------------------------------------------------------Set plane id %d prop->prop_id %d zpos %d", pPlane->plane_id, prop->prop_id, zpos);
               
      
            }else if (prop && strcmp(prop->name, "zpos") == 0 && (pPlane->plane_id == m_arrayDrmIniConf[0].plane_id)) {

                  drmModeObjectSetProperty(m_fd, pPlane->plane_id, DRM_MODE_OBJECT_PLANE, prop->prop_id, m_arrayDrmIniConf[0].plane_zpos);
                  consolePrint("-----------------------------------------------------------------------------Set plane id %d prop->prop_id %d zpos %d", pPlane->plane_id, prop->prop_id, zpos);

            }
            else if (prop && strcmp(prop->name, "zpos") == 0 && (pPlane->plane_id == 116 )) {

                  drmModeObjectSetProperty(m_fd, pPlane->plane_id, DRM_MODE_OBJECT_PLANE, prop->prop_id, 0);
                  consolePrint("-----------------------------------------------------------------------------Set plane id %d prop->prop_id %d zpos %d", pPlane->plane_id, prop->prop_id, zpos);

            }
            // if (prop && strcmp(prop->name, "type") == 0 && pPlane->plane_id == PLANEID_DSI)
            // {
            //    //drmModeObjectSetProperty(m_fd, pPlane->plane_id, DRM_MODE_OBJECT_PLANE, prop->prop_id, 1);
            //    for (size_t k = 0; k < prop->count_enums; k++)
            //    {
            //       consolePrint("------------------------------------type name: %s value :%d-----------------------------------------", prop->enums[k].name, prop->enums[k].value);
            //    }
               
            //    for (size_t n = 0; n < prop->count_values; n++)
            //    {
            //       consolePrint("------------------------------------type value[%d] :%d-----------------------------------------", n, prop->values[n]);
            //    }
               
            // }
            
            drmModeFreeProperty(prop);
         }
         drmModeFreePlane(pPlane);
      }
      
   }
   drmModeFreePlaneResources(planeRes);
   return true;
}

uint32_t DrmController::getProperty(int fd, drmModeObjectProperties *props, const char *name)
{
	drmModePropertyPtr property;
	uint32_t i, id = 0;

	/* find property according to the name */
	for (i = 0; i < props->count_props; i++) {
		property = drmModeGetProperty(fd, props->props[i]);
		if (!strcmp(property->name, name))
			id = property->prop_id;
		drmModeFreeProperty(property);

		if (id)
			break;
	}

	return id;
}

int DrmController::drmdisplayFindCrtc(drmModeRes *res, drmModeConnector *conn, DrmDisplayDev *dev)
{
  drmModeEncoder *enc;
	int i, j;
	int32_t crtc;
	struct DrmDisplayDev *iter;

	/* first try the currently conected encoder+crtc */
	if (conn->encoder_id)
		enc = drmModeGetEncoder(m_fd, conn->encoder_id);
	else
		enc = NULL;

	if (enc) {
		if (enc->crtc_id) {
			crtc = enc->crtc_id;
			for (iter = m_drmdisplayList; iter; iter = iter->next) {
				if (iter->crtc == crtc) {
					crtc = -1;
					break;
				}
			}

			if (crtc >= 0) {
				drmModeFreeEncoder(enc);
				dev->crtc = crtc;
				return 0;
			}
		}

		drmModeFreeEncoder(enc);
	}

	/* If the connector is not currently bound to an encoder or if the
	 * encoder+crtc is already used by another connector (actually unlikely
	 * but lets be safe), iterate all other available encoders to find a
	 * matching CRTC. */
	for (i = 0; i < conn->count_encoders; ++i) {
		enc = drmModeGetEncoder(m_fd, conn->encoders[i]);
		if (!enc) {
			consolePrint("cannot retrieve encoder %u:%u (%d)", i, conn->encoders[i], errno);
			continue;
		}

		/* iterate all global CRTCs */
		for (j = 0; j < res->count_crtcs; ++j) {
			/* check whether this CRTC works with the encoder */
			if (!(enc->possible_crtcs & (1 << j)))
				continue;

			/* check that no other device already uses this CRTC */
			crtc = res->crtcs[j];
			for (iter = m_drmdisplayList; iter; iter = iter->next) {
				if (iter->crtc == crtc) {
					crtc = -1;
					break;
				}
			}

			/* we have found a CRTC, so save it and return */
			if (crtc >= 0) {
				drmModeFreeEncoder(enc);
				dev->crtc = crtc;
				return 0;
			}
		}

		drmModeFreeEncoder(enc);
	}

	consolePrint("cannot find suitable CRTC for connector %u",conn->connector_id);
	return -ENOENT;
}

int DrmController::drmdisplayCreateFb(DrmDisplayDev *dev)
{
  struct drm_mode_create_dumb creq;
	struct drm_mode_destroy_dumb dreq;
	struct drm_mode_map_dumb mreq;
	int ret;

    /* create dumb buffer */
    memset(&creq, 0, sizeof(creq));

    creq.width = dev->width;
    creq.height = dev->height;
    creq.bpp = 24;

	ret = drmIoctl(m_fd, DRM_IOCTL_MODE_CREATE_DUMB, &creq);
	if (ret < 0) {
		consolePrint("cannot create dumb buffer (%d)",errno);
		return -errno;
	}

	dev->stride = creq.pitch;
	dev->size = creq.size;
	dev->handle = creq.handle;

    /* create framebuffer object for the dumb-buffer */
	ret = drmModeAddFB(m_fd, dev->width, dev->height, 24, 24, dev->stride,
			   dev->handle, &dev->fb);
	if (ret) {
		consolePrint("cannot create framebuffer (%d)",errno);
		ret = -errno;
		memset(&dreq, 0, sizeof(dreq));
		dreq.handle = dev->handle;
		drmIoctl(m_fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);
		return ret;
	}

	/* prepare buffer for memory mapping */
	memset(&mreq, 0, sizeof(mreq));
	mreq.handle = dev->handle;
	ret = drmIoctl(m_fd, DRM_IOCTL_MODE_MAP_DUMB, &mreq);
	if (ret) {
		consolePrint("cannot map dumb buffer (%d)", errno);
		ret = -errno;
		drmModeRmFB(m_fd, dev->fb);
		return ret;
	}

	/* perform actual memory mapping */
	// dev->map = mmap(0, dev->size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mreq.offset);
	dev->map = static_cast<uint8_t *>(mmap(0, dev->size, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, mreq.offset));
	if (dev->map == MAP_FAILED) {
		consolePrint("cannot mmap dumb buffer (%d)", errno);
		ret = -errno;
		drmModeRmFB(m_fd, dev->fb);
		return ret;
	}

	/* clear the framebuffer to 0 */
	memset(dev->map, 0, dev->size);

	return 0;
}

int DrmController::drmdisplaySetupDev(drmModeRes *res, drmModeConnector *conn, DrmDisplayDev *dev)
{
  int ret;

	/* check if a monitor is connected */
	if (conn->connection != DRM_MODE_CONNECTED) {
		consolePrint("ignoring unused connector %u", conn->connector_id);
		return -ENOENT;
	}

	/* check if there is at least one valid mode */
	if (conn->count_modes == 0) {
		consolePrint("no valid mode for connector %u", conn->connector_id);
		return -EFAULT;
	}

	/* copy the mode information into our device structure */
	memcpy(&dev->mode, &conn->modes[0], sizeof(dev->mode));
	dev->width = conn->modes[0].hdisplay;
	dev->height = conn->modes[0].vdisplay;
	consolePrint("mode for connector %u is %ux%u", conn->connector_id, dev->width, dev->height);

	/* find a crtc for this connector */
	ret = drmdisplayFindCrtc(res, conn, dev);
	if (ret) {
		consolePrint("no valid crtc for connector %u", conn->connector_id);
		return ret;
	}

	/* create a framebuffer for this CRTC */
	ret = drmdisplayCreateFb(dev);
	if (ret) {
		consolePrint("cannot create framebuffer for connector %u", conn->connector_id);
		return ret;
	}

	return 0;
}

int DrmController::drmdisplayOpen(int *out, const char *node)
{
   int fd, ret;
   uint64_t has_dumb;

   fd = open(node, O_RDWR | O_CLOEXEC);
   if (fd < 0)
   {
      ret = -errno;
      consolePrint( "open file fail: %d",ret);
      return ret;
   }

   if (drmGetCap(fd, DRM_CAP_DUMB_BUFFER, &has_dumb) < 0 || !has_dumb)
   {
      consolePrint("drm device '%s' does not support dumb buffers ",node);
      close(fd);
      return -EOPNOTSUPP;
   }

   *out = fd;
   return 0;
}

int DrmController::drmdisplayPrepare()
{
   drmModeRes *res;
	drmModeConnector *conn;
	drmModePlaneRes *plane_res;
	int i;
	struct DrmDisplayDev *dev;
	int ret;
	uint32_t plane_id1;

	/* retrieve resources */
	res = drmModeGetResources(m_fd);
	if (!res) {
		consolePrint("cannot retrieve DRM resources (%d)", errno);
		return -errno;
	}

	drmSetClientCap(m_fd, DRM_CLIENT_CAP_UNIVERSAL_PLANES, 1);
   drmSetClientCap(m_fd, DRM_CLIENT_CAP_ATOMIC, 1);

	plane_res = drmModeGetPlaneResources(m_fd);

   consolePrint("Plane count %d", plane_res->count_planes);
   for(int i = 0; i < plane_res->count_planes; i++) {
      consolePrint("Plane id %d", plane_res->planes[i]);
   }
	plane_id1 = plane_res->planes[0];

	/* iterate all connectors */
	consolePrint("drmdisplay_prepare res->count_connectors (%d)", res->count_connectors);
	for (i = 0; i < res->count_connectors; ++i) {
		/* get information for each connector */
		conn = drmModeGetConnector(m_fd, res->connectors[i]);
		if (!conn) {
			consolePrint("cannot retrieve DRM connector %u:%u (%d)", i, res->connectors[i], errno);
			continue;
		}

		/* create a device structure */
		// dev = malloc(sizeof(*dev));
     	dev = (struct DrmDisplayDev *)malloc(sizeof(struct DrmDisplayDev));
		memset(dev, 0, sizeof(*dev));
		dev->conn = conn->connector_id;
      if(i == 0) {
         dev->plane_id = m_arrayDrmIniConf[1].plane_id;
      }else if(i == 1) {
         dev->plane_id = m_arrayDrmIniConf[2].plane_id;
      }else if(i == 2) {
         dev->plane_id = m_arrayDrmIniConf[0].plane_id;
      }else {
         dev->plane_id = plane_id1;
      }
      consolePrint("plane_id1[%d] %d", i, dev->plane_id);
		/* call helper function to prepare this connector */
		ret = drmdisplaySetupDev(res, conn, dev);
		if (ret) {
			if (ret != -ENOENT) {
				errno = -ret;
				consolePrint("cannot setup device for connector %u:%u (%d):", i, res->connectors[i], errno);
			}
			free(dev);
			drmModeFreeConnector(conn);
			continue;
		}
      consolePrint("drmdisplay_setup_dev: crtc id: %d connect id:%d plane id %d size %d", dev->crtc, dev->conn, dev->plane_id, dev->size);
		/* free connector data and link device into global list */
		drmModeFreeConnector(conn);
		dev->next = m_drmdisplayList;
		m_drmdisplayList = dev;
      if (i== 2)
      {
         break;
      }
      
	}

	/* free resources again */
	drmModeFreeResources(res);
	return 0;
}

void DrmController::drmdisplayCleanup()
{
   struct DrmDisplayDev *iter;
	struct drm_mode_destroy_dumb dreq;
   std::lock_guard<std::mutex> lc(m_mutex);
	while (m_drmdisplayList) {
		/* remove from global list */
		iter = m_drmdisplayList;
		m_drmdisplayList = iter->next;
		/* restore saved CRTC configuration */
		// drmModeSetCrtc(m_fd,
		// 	       iter->saved_crtc->crtc_id,
		// 	       iter->saved_crtc->buffer_id,
		// 	       iter->saved_crtc->x,
		// 	       iter->saved_crtc->y,
		// 	       &iter->conn,
		// 	       1,
		// 	       &iter->saved_crtc->mode);
      // drmModeSetCrtc(m_fd,
      // iter->saved_crtc->crtc_id,
      // 0,
      // 0,
      // 0,
      // 0,
      // 1,
      // &iter->saved_crtc->mode);
		// drmModeFreeCrtc(iter->saved_crtc);

		/* unmap buffer */
		munmap(iter->map, iter->size);

		/* delete framebuffer */
		drmModeRmFB(m_fd, iter->fb);

		/* delete dumb buffer */
		memset(&dreq, 0, sizeof(dreq));
		dreq.handle = iter->handle;
		drmIoctl(m_fd, DRM_IOCTL_MODE_DESTROY_DUMB, &dreq);

		/* free allocated memory */
		free(iter);
	}
   if(m_fd > 0) {
      close(m_fd);
      m_fd = 0;
   }   
}

bool DrmController::displayImage(ImageLoader &imageData, long size, uint32_t width, uint32_t height)
{
     if(m_fd <= 0)
      return false;
   consolePrint("displayImage size %dl width: %d, height: %d subdata size %d", size, width, height, imageData.getSubData(0).size());
   //consolePrint("start  set CRTC ...m_arrayBufferObj.size() %d ", m_arrayBufferObj.size());
   static bool inited = false;

   //for (int i = 0; i < m_arrayBufferObj.size(); i++)
   int i = 0;
   std::lock_guard<std::mutex> lk(m_mutex);
   for (DrmDisplayDev* iter = m_drmdisplayList; iter; iter = iter->next) 
   {
      consolePrint("===========================================iter->plane_id :%d crtc %d-============================", iter->plane_id, iter->crtc);
      if (!inited)
      {
        
         auto startTime = std::chrono::high_resolution_clock::now();
         drmModeObjectProperties *props;
         drmModeAtomicReq *req;
         uint32_t property_crtc_id;
         uint32_t property_mode_id;
         uint32_t property_active;
         uint32_t property_fb_id;
         uint32_t property_crtc_x;
         uint32_t property_crtc_y;
         uint32_t property_crtc_w;
         uint32_t property_crtc_h;
         uint32_t property_src_x;
         uint32_t property_src_y;
         uint32_t property_src_w;
         uint32_t property_src_h;

         auto endTime2 = std::chrono::high_resolution_clock::now();
         auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - startTime);
         consolePrint("[memcpy[%d]] buffer spend %d ms", i, duration2.count());

         /* get plane properties */
         props = drmModeObjectGetProperties(m_fd,  iter->plane_id, DRM_MODE_OBJECT_PLANE);
         property_crtc_id = getProperty(m_fd, props, "CRTC_ID");
         property_fb_id = getProperty(m_fd, props, "FB_ID");
         property_crtc_x = getProperty(m_fd, props, "CRTC_X");
         property_crtc_y = getProperty(m_fd, props, "CRTC_Y");
         property_crtc_w = getProperty(m_fd, props, "CRTC_W");
         property_crtc_h = getProperty(m_fd, props, "CRTC_H");
         property_src_x = getProperty(m_fd, props, "SRC_X");
         property_src_y = getProperty(m_fd, props, "SRC_Y");
         property_src_w = getProperty(m_fd, props, "SRC_W");
         property_src_h = getProperty(m_fd, props, "SRC_H");
         drmModeFreeObjectProperties(props);

         /* atomic plane update */
         req = drmModeAtomicAlloc();
         drmModeAtomicAddProperty(req, iter->plane_id, property_crtc_id, iter->crtc);
         drmModeAtomicAddProperty(req, iter->plane_id, property_fb_id, iter->fb);
         drmModeAtomicAddProperty(req, iter->plane_id, property_crtc_x, 0);
         drmModeAtomicAddProperty(req, iter->plane_id, property_crtc_y, 0);
         drmModeAtomicAddProperty(req, iter->plane_id, property_crtc_w, iter->width);
         drmModeAtomicAddProperty(req, iter->plane_id, property_crtc_h, iter->height);
         drmModeAtomicAddProperty(req, iter->plane_id, property_src_x, 0 << 16);
         drmModeAtomicAddProperty(req, iter->plane_id, property_src_y, 0 << 16);
         drmModeAtomicAddProperty(req, iter->plane_id, property_src_w, iter->width << 16);
         drmModeAtomicAddProperty(req, iter->plane_id, property_src_h, iter->height << 16);
         drmModeAtomicCommit(m_fd, req, 0, NULL);
         drmModeAtomicFree(req);

         auto endTime = std::chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
         consolePrint("[drmModeAtomicCommit[%d]] buffer spend %d ms", i, duration.count());
         
      }
      
      auto startTime = std::chrono::high_resolution_clock::now();
      if (iter->plane_id == m_arrayDrmIniConf[0].plane_id) {
         memcpy(iter->map, (uint8_t*)imageData.getSubData(-1).data(), iter->size);
      } else if (iter->plane_id == m_arrayDrmIniConf[1].plane_id) {
         memcpy(iter->map, (uint8_t*)imageData.getSubData(-1).data(), iter->size);
      } else if (iter->plane_id == m_arrayDrmIniConf[2].plane_id) {
         memcpy(iter->map, (uint8_t*)imageData.getSubData(-1).data(), iter->size);
      }
     // memcpy(iter->map, (uint8_t*)imageData.getSubData(i).data(), iter->size);
      auto endTime2 = std::chrono::high_resolution_clock::now();
      auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime2 - startTime);
      consolePrint("[memcpy[%d]] buffer spend %d ms size: %llu", i, duration2.count(), iter->size);
      
      i++;

   }
   inited = true;
   consolePrint("end display");
   
   return true;
}

void DrmController::showCluster(bool bShow)
{
   if (!bShow)
   {
      unDisplay(m_fd, 220);
   }
   
   
}

void DrmController::showIVI(bool bShow)
{
   if (!bShow) {
      unDisplay(m_fd, 56);
      unDisplay(m_fd, 76);
   }
}

void DrmController::unInit()
{
   drmdisplayCleanup();
}

bool DrmController::initWithIni()
{
   std::fstream file(DRM_INI_CONFIG);
   if(!file) {
      consolePrint("File is not exist...");
      return false;
   }
   boost::property_tree::ptree pt;  
   boost::property_tree::ini_parser::read_ini(DRM_INI_CONFIG, pt); 

   int crtcDSI1 = pt.get<int>("CRTC.DSI1");  
   int crtcHDMI1 = pt.get<int>("CRTC.HDMI1"); 
   int crtcHDMI2 = pt.get<int>("CRTC.HDMI2"); 

   int planecDSI1 = pt.get<int>("PLANE.DSI1"); 
   int planecHDMI1 = pt.get<int>("PLANE.HDMI1"); 
   int planecHDMI2 = pt.get<int>("PLANE.HDMI2"); 

   int planeZposDSI1 = pt.get<int>("PLANE_ZPOS.DSI1");
   int planeZposHDMI1 = pt.get<int>("PLANE_ZPOS.HDMI1"); 
   int planeZposHDMI2 = pt.get<int>("PLANE_ZPOS.HDMI2"); 

   m_arrayDrmIniConf[0].plane_id = planecDSI1;
   m_arrayDrmIniConf[1].plane_id = planecHDMI1;
   m_arrayDrmIniConf[2].plane_id = planecHDMI2;

   m_arrayDrmIniConf[0].crtc_id = crtcDSI1;
   m_arrayDrmIniConf[1].crtc_id = crtcHDMI1;
   m_arrayDrmIniConf[2].crtc_id = crtcHDMI2;

   m_arrayDrmIniConf[0].plane_zpos = planeZposDSI1;
   m_arrayDrmIniConf[1].plane_zpos = planeZposHDMI1;
   m_arrayDrmIniConf[2].plane_zpos = planeZposHDMI2;


   consolePrint("Init configure values: [crtcDSI1:%d] [crtcHDMI1:%d] [crtcHDMI2:%d]", crtcDSI1, crtcHDMI1, crtcHDMI2);
   consolePrint("Init configure values: [planecDSI1:%d] [planecHDMI1:%d] [planecHDMI2:%d]", planecDSI1, planecHDMI1, planecHDMI2);
   
   return true;
}

DrmController::DrmController()
{
   // Init with default values.
   m_arrayDrmIniConf[0].crtc_id = 130;
   m_arrayDrmIniConf[1].crtc_id = 70;
   m_arrayDrmIniConf[2].crtc_id = 70;

   m_arrayDrmIniConf[0].plane_id = 220;
   m_arrayDrmIniConf[1].plane_id = 56;
   m_arrayDrmIniConf[2].plane_id = 76;

   m_arrayDrmIniConf[0].plane_zpos = 6;
   m_arrayDrmIniConf[1].plane_zpos = 1;
   m_arrayDrmIniConf[2].plane_zpos = 1;
}

DrmController::~DrmController()
{
   drmdisplayCleanup();
}
#endif
