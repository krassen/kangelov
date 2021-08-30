class Post < ActiveRecord::Base
  #attr_accesser :title, :content # not work in rails 4
  validates :title, :content, :presence => true
  validates :title, :length => { :minimum => 2 }
  validates :title, :uniqueness => { :massage => "already taken" }
end
