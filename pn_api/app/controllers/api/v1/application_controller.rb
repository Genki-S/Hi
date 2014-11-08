class Api::V1::ApplicationController < ApplicationController
  after_filter :cors_set_access_control_headers

  # respond to options requests with blank text/plain as per spec
  def cors_preflight_check
    render :text => '', :content_type => 'text/plain'
  end

  # For all responses in this controller, return the CORS access control headers. 
  def cors_set_access_control_headers
    headers['Access-Control-Allow-Origin'] = '*'
    headers['Access-Control-Allow-Headers'] = 'X-AUTH-TOKEN, X-API-VERSION, X-Requested-With, Content-Type, Accept, Origin'
    headers['Access-Control-Allow-Methods'] = 'POST, GET, PUT, DELETE, OPTIONS'
    headers['Access-Control-Max-Age'] = "1728000"
  end
end
