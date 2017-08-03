//
//  Created by zhanghao on 2017/4/30.
//  Copyright © 2017年 zhanghao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "zhDatabaseProtocol.h"
#import "FMDB.h"

NS_ASSUME_NONNULL_BEGIN

@interface zhDatabaseCore : NSObject

+ (instancetype)sharedInstance;

- (void)inDatabase:(id <zhDatabaseProtocol>)object database:(void(^)(FMDatabase* db))block;

- (void)inDatabase:(id <zhDatabaseProtocol>)object transaction:(void (^)(FMDatabase *db, BOOL *rollback))block;

/// 是否存在该表
- (BOOL)tableExists:(id<zhDatabaseProtocol>)object;

/// 删除表
- (BOOL)dropTableWithObject:(id<zhDatabaseProtocol>)object;

/// 修改表名
- (BOOL)renameTableWithObject:(id<zhDatabaseProtocol>)object newName:(NSString *)newName;

/**
 *  @brief 创建表或升级表
 *  - ALTER TABLE... (命令允许重命名或添加新的字段在已有表中，不能从表中删除字段。并且只能在表的末尾添加字段)
 */
- (BOOL)createTableWithObject:(id<zhDatabaseProtocol>)object;

/**
 *  @brief 插入数据
 *  - 需要按字段顺序设置values
 */
- (BOOL)saveObject:(id<zhDatabaseProtocol>)object values:(NSArray *)values;

/// 忽略插入相同数据
- (BOOL)saveIgnoreObject:(id<zhDatabaseProtocol>)object values:(NSArray *)values;

/// 删除数据（byCriteriaWithFormat传入nil时，则清空表中所有数据）
- (BOOL)deleteObject:(id<zhDatabaseProtocol>)object byCriteriaWithFormat:(nullable NSString *)format, ...;

/// 手写sql删除语句
- (BOOL)deleteObject:(id<zhDatabaseProtocol>)object sqlWithFormat:(NSString *)format, ... ;

/// 更新数据
- (BOOL)updateObject:(id<zhDatabaseProtocol>)object setKeys:(NSString *)setKeys byCriteria:(NSString *)criteria;

/// 手写sql更新语句
- (BOOL)updateObject:(id<zhDatabaseProtocol>)object sqlWithFormat:(NSString *)format, ... ;


/// 查询数据（byCriteriaWithFormat传入nil时，则查询表中所有数据）
- (NSArray *)selectObject:(id<zhDatabaseProtocol>)object byCriteriaWithFormat:(nullable NSString *)format, ... ;

/**
 *  @brief 条件查询
 *
 *  @param orderKey 根据该字段查询
 *  @param descSort YES 降序查询 / NO 升序查询
 *  @param limitCount 限制查询条数
 *  @param format 查询条件
 *
 *  @return 符合<SnailDatabaseProtocol>协议的object数组
 */
- (NSArray *)selectObject:(id<zhDatabaseProtocol>)object orderKey:(nullable NSString *)orderKey descSort:(BOOL)descSort limitCount:(NSInteger)limitCount byCriteriaWithFormat:(nullable NSString *)format, ...;

/// 手写sql查询语句
- (NSArray *)selectObject:(id<zhDatabaseProtocol>)object sqlWithFormat:(NSString *)format, ... ;

#pragma mark - 采用自动属性映射并为之提供的方法

/**
 *  @brief 创建表(自动属性映射)
 *
 *  @param description 设置主键或约束
 *
 *  @example NSString *description = @"primary key(name), unique(name1, name2)";
 */
- (BOOL)mapColumnCreateTableWithObject:(id<zhDatabaseProtocol>)object appendPrimaryKeyAndUniqueKeys:(nullable NSString *)description;

/// 保存数据(自动属性映射)
- (BOOL)mapColumnSaveObject:(id<zhDatabaseProtocol>)object;

/// 根据主键或约束字段忽略保存数据
- (BOOL)mapColumnSaveIgnoreObject:(id<zhDatabaseProtocol>)object;

/// 查询数据(自动属性映射)
- (NSArray *)mapColumnSelectObject:(id<zhDatabaseProtocol>)object byCriteriaWithFormat:(nullable NSString *)format, ... ;

/// 条件查询(自动属性映射)
- (NSArray *)mapColumnSelectObject:(id<zhDatabaseProtocol>)object
                          orderKey:(nullable NSString *)orderKey
                          descSort:(BOOL)descSort
                        limitCount:(NSInteger)limitCount
              byCriteriaWithFormat:(nullable NSString *)format, ...;

/// 手写sql查询语句(自动属性映射)
- (NSArray *)mapColumnSelectObject:(id<zhDatabaseProtocol>)object sqlWithFormat:(NSString *)format, ... ;

@end

#define FMDB ([zhDatabaseCore sharedInstance])

NS_ASSUME_NONNULL_END
